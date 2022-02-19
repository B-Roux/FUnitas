#ifndef ONCE_FLIST_HPP
#define ONCE_FLIST_HPP

#include "../FMacros.hpp"
#include "FBlock.hpp"
#include "FRange.hpp"

FNAMESPACE {

template <typename T> class FList {

private:
    FBlock<T>* head;
    FBlock<T>* tail;
    fuint total_length;
    bool defragmented;

protected:

    /// <summary>
    /// Add the array block as an FBlock to this FList.
    /// WARNING: The passed array should not be deleted. 
    /// Do not use this if you don't have a very good reason to.
    /// Intended for internal use ONLY.
    /// </summary>
    /// <returns>void</returns>
    void integrate_array(T* block, const fuint length) {
        if (head == nullptr) {
            this->head = new FBlock<T>(block, length, this->total_length);
            this->tail = this->head;
        }
        else {
            FBlock<T>* tmp = new FBlock<T>(block, length, this->total_length);
            tmp->prev = this->tail;
            this->tail->next = tmp;
            this->tail = tmp;
        }
        this->total_length += length;
    }

    /// <summary>
    /// Allocate and return a pointer to an array containing all records
    /// in this FList.
    /// WARNING: The returned array is not deleted automatically. 
    /// Do not use this if you don't have a very good reason to.
    /// Intended for internal use ONLY.
    /// </summary>
    /// <returns>T*</returns>
    T* export_array() const {

        T* buffer = new T[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i];
                ++j;
            }
            read = read->next;
        }
        return buffer;
    }

public:

    //BASIC OPPERATORS

    /// <summary>
    /// Public getter for array length
    /// </summary>
    /// <returns>uint</returns>
    fuint length() const {
        return this->total_length;
    }

    /// <summary>
    /// Appends the contents of op to this FList (op is not affected).
    /// </summary>
    /// <returns>void</returns>
    void append(const FList<T>& op) {
        this->integrate_array(op.export_array(), op.length());

        //set flag
        this->defragmented = false;
    }

    /// <summary>
    /// Appends op to this FList (op assignment called).
    /// </summary>
    /// <returns>void</returns>
    void append(const T op) {
        T* buffer = new T[1];
        buffer[0] = op;
        this->integrate_array(buffer, 1);

        //set flag
        this->defragmented = false;
    }

    /// <summary>
    /// Reallocate this FList so all data is contiguous
    /// (ensures array accesses with [] return in O(1) time).
    /// </summary>
    /// <returns>void</returns>
    void defragment() {

        //if already defragged, nothing needs to be done :)
        if (this->defragmented) {
            return;
        }

        //allocate contiguous block
        T* buffer = this->export_array();
        fuint len = this->length();

        //release currently held memory
        FBlock<T>* read = this->head;
        FBlock<T>* read_next = nullptr;
        while (read != nullptr) {
            read_next = read->next;
            delete read;
            read = read_next;
        }

        //reset internal state
        this->head = nullptr;
        this->tail = nullptr;
        this->total_length = 0;

        //reinstantiate
        this->integrate_array(buffer, len);

        //set flag
        this->defragmented = true;
    }

#ifdef FINIT_LIST
    /// <summary>
    /// Appends the initializer list to this FList.
    /// </summary>
    /// <returns>void</returns>
    void append (const std::initializer_list<T> values) {

        //append the new internals
        T* block = new T[values.size()];
        fuint i = 0;
        for (T item : values) {
            block[i] = item;
            ++i;
        }
        this->integrate_array(block, i);

        //set flag
        this->defragmented = false;
    }
#endif

    /// <summary>
    /// Applies mapper(T) to every T in this FList.
    /// </summary>
    /// <returns>void</returns>
    void map (T(*mapper)(T)) {
        FBlock<T>* read = this->head;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                read->block[i] = (*mapper)(read->block[i]);
            }
            read = read->next;
        }
    }

    /// <summary>
    /// applies func(T, fuint) to every record T (index fuint) in 
    /// the FList.
    /// </summary>
    /// <returns>FList<S></returns>
    template <typename S> 
    FList<S> for_each (S(*func)(T, fuint)) {
        FBlock<T>* read = this->head;
        S* buffer = new S[this->total_length];
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = (*func)(read->block[i], j);
                ++j;
            }
            read = read->next;
        }

        return FList<S>(buffer, this->total_length);
    }

    /// <summary>
    /// Index the idx(th) item in this FList.
    /// Error if out of bounds.
    /// </summary>
    /// <returns>A single record T</returns>
    T& operator [] (const fuint idx) const {
        FBlock<T>* read = tail;
        if ((idx >= this->total_length) || (idx < 0)) {
            throw std::out_of_range("Index out of Bounds");
        }
        while (read != nullptr) {
            if (idx < read->start_indx) {
                read = read->prev;
            }
            else {
                return read->block[idx - read->start_indx];
            }
        }
        throw std::out_of_range("Index out of Bounds");
    }

    /// <summary>
    /// Get the sub-FList starting at idx.start and ending at idx.end-1.
    /// If idx.end is too large, return to the maximum index.
    /// Error if idx.start > idx.end-1
    /// </summary>
    /// <returns>An FList containing the sub-FList</returns>
    FList<T> operator [] (const FRange idx) const {
        fuint start = idx.start;
        fuint end = (idx.end <= this->total_length) ? idx.end : this->total_length;

        bool reverse = idx.by < 0;
        fuint by = (fuint)(reverse ? -idx.by : idx.by); //abs of by

        if ((start >= this->total_length) || (start > end)) {
            throw std::out_of_range("Index out of Bounds");
        }

        //The size of the buffer needed (the OBOE were weird, but this "works")
        fuint buff_size = (end - start - 1) / by + 1;

        T* buffer = new T[buff_size];
        FBlock<T>* read = head;
        fuint j = 0;
        fuint k = 0;
        int to_skip = 0;
        while (read != nullptr) {
            //i: loop through the data block
            //j: loop through this FList
            //k: loop through the out array
            for (fuint i = 0; i < read->block_size; i++) {
                if ((j >= start) && (j < end)) {
                    if (to_skip == 0) {
                        buffer[k] = read->block[i];
                        ++k;
                        to_skip = by;
                    }
                    --to_skip;
                }
                ++j;
            }
            read = read->next;
        }

        if (reverse) {
            for (fuint i = 0; i < buff_size / 2; i++) {
                fuint j = buff_size - i - 1;
                T temp = buffer[i];
                buffer[i] = buffer[j];
                buffer[j] = temp;
            }
        }

        return FList<T>(buffer, buff_size);
    }

    /// <summary>
    /// Get every item of this FList where logical is true.
    /// Error if dimensions don't match.
    /// </summary>
    /// <returns>An FList containing the sub-FList</returns>
    FList<T> operator [] (const FList<bool>& logical) const {
        if (logical.length() != this->total_length) {
            throw std::out_of_range("Dimensional Mismatch");
        }

        fuint n_true = 0;

        for (fuint i = 0; i < logical.length(); i++) {
            if (logical[i]) {
                ++n_true;
            }
        }
        if (n_true > 0) {
            T* buffer = new T[n_true];
            for (fuint i = 0, j = 0; i < logical.length(); i++) {
                if (logical[i]) {
                    buffer[j] = this->operator[](i);
                    ++j;
                }
            }
            return FList<T>(buffer, n_true);
        }
        else {
            return FList<T>();
        }
    }

    /// <summary>
    /// Deep copy op and assign it to this instance.
    /// (Deletes any currently held data.)
    /// </summary>
    /// <returns>void</returns>
    void operator = (const FList<T>& op) {

        //release currently held memory
        FBlock<T>* read = this->head;
        FBlock<T>* read_next = nullptr;
        while (read != nullptr) {
            read_next = read->next;
            delete read;
            read = read_next;
        }

        //reset internal state
        this->head = nullptr;
        this->tail = nullptr;
        this->total_length = 0;

        //instantiate from op
        this->integrate_array(op.export_array(), op.length());
    }

#ifdef FINIT_LIST
    /// <summary>
    /// Assign all values in the initializer list to this instance.
    /// (Deletes any currently held data.)
    /// </summary>
    /// <returns>void</returns>
    void operator = (const std::initializer_list<T> values) {

        //release currently held memory
        FBlock<T>* read = this->head;
        FBlock<T>* read_next = nullptr;
        while (read != nullptr) {
            read_next = read->next;
            delete read;
            read = read_next;
        }

        //reset internal state
        this->head = nullptr;
        this->tail = nullptr;
        this->total_length = 0;

        //set the new internals
        T* block = new T[values.size()];
        fuint i = 0;
        for (T item : values) {
            block[i] = item;
            ++i;
        }
        this->integrate_array(block, i);
    }
#endif

    //COMPARISON OPERATORS

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList (bool) where this is gt op</returns>
    FList<bool> operator > (const FList<T>& op) const & {
        if (op.length() != this->total_length) {
            throw std::out_of_range("Dimensional Mismatch");
        }

        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] > op[j];
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this[] > op</returns>
    FList<bool> operator > (const T& op) const & {
        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] > op;
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this < op</returns>
    FList<bool> operator < (const FList<T>& op) const & {
        if (op.length() != this->total_length) {
            throw std::out_of_range("Dimensional Mismatch");
        }

        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] < op[j];
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this[] < op</returns>
    FList<bool> operator < (const T& op) const & {
        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] < op;
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this >= op</returns>
    FList<bool> operator >= (const FList<T>& op) const {
        if (op.length() != this->total_length) {
            throw std::out_of_range("Dimensional Mismatch");
        }

        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] >= op[j];
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this[] >= op</returns>
    FList<bool> operator >= (const T& op) const {
        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] >= op;
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this <= op</returns>
    FList<bool> operator <= (const FList<T>& op) const {
        if (op.length() != this->total_length) {
            throw std::out_of_range("Dimensional Mismatch");
        }

        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] <= op[j];
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this[] <= op</returns>
    FList<bool> operator <= (const T& op) const {
        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] <= op;
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }


    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this == op</returns>
    FList<bool> operator == (const FList<T>& op) const {
        if (op.length() != this->total_length) {
            throw std::out_of_range("Dimensional Mismatch");
        }

        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] == op[j];
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this[] == op</returns>
    FList<bool> operator == (const T& op) const {
        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] == op;
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this != op</returns>
    FList<bool> operator != (const FList<T>& op) const {
        if (op.length() != this->total_length) {
            throw std::out_of_range("Dimensional Mismatch");
        }

        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] != op[j];
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }


    /// <summary>
    /// Compare op to this FList.
    /// </summary>
    /// <returns>An FList<bool> where this[] != op</returns>
    FList<bool> operator != (const T& op) const {
        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = read->block[i] != op;
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    /// <summary>
    /// Negate this FList.
    /// </summary>
    /// <returns>An FList<bool> where !this[]</returns>
    FList<bool> operator ! () const & {
        bool* buffer = new bool[this->total_length];
        FBlock<T>* read = this->head;
        fuint j = 0;
        while (read != nullptr) {
            for (fuint i = 0; i < read->block_size; i++) {
                buffer[j] = !(read->block[i]);
                ++j;
            }
            read = read->next;
        }

        return FList<bool>(buffer, this->total_length);
    }

    //MISCILLANEOUS OPERATORS (FRIEND FUNCTIONS)
#ifdef FIOSTREAM
    /// <summary>
    /// Add this FList to the OStream.
    /// </summary>
    /// <returns>std::ostream&</returns>
    friend std::ostream& operator <<(std::ostream& os, FList<T> list) {
        os << "[";
        for (fuint i = 0; i < list.length(); i++) {
            if (i > 0) {
                os << ", ";
            }
            os << list[i];
        }
        os << "]";
        return os;
    }
#endif

    //CONSTRUCTORS & DECONSTRUCTORS

    /// <summary>
    /// Initialize an empty FList.
    /// </summary>
    /// <returns>FList<T></returns>
    FList<T>() {

        this->head = nullptr;
        this->tail = nullptr;
        this->total_length = 0;

        //set flag
        this->defragmented = true;
    }

    /// <summary>
    /// Create an FList from an array and a length value.
    /// WARNING: The passed array is not to be deleted. 
    /// Do not use this if you don't have a very good reason to.
    /// </summary>
    /// <returns>FList<T></returns>
    FList<T>(T* block, fuint length) {

        this->head = new FBlock<T>(block, length, 0);
        this->tail = this->head;
        this->total_length = length;

        //set flag
        this->defragmented = true;
    }

    //TODO: Maybe make this a shallow copy?
    /// <summary>
    /// Deep copy this FList.
    /// </summary>
    /// <returns>FList<T></returns>
    FList<T>(const FList<T>& old) {

        this->head = new FBlock<T>(old.export_array(), old.length(), 0);
        this->tail = this->head;
        this->total_length = old.length();

        //set flag
        this->defragmented = true;
    }

#ifdef FINIT_LIST
    /// <summary>
    /// Create an FList from an initializer list.
    /// </summary>
    /// <returns>FList (of T)</returns>
    FList<T>(std::initializer_list<T> values) {

        T* block = new T[values.size()];
        fuint i = 0;
        for (T item : values) {
            block[i] = item;
            ++i;
        }

        this->head = new FBlock<T>(block, i, 0);
        this->tail = this->head;
        this->total_length = i;

        //set flag
        this->defragmented = true;
    }
#endif

    /// <summary>
    /// Deconstruct this FList.
    /// Do not explicitly use this if you don't have a 
    /// very good reason to.
    /// </summary>
    /// <returns>void</returns>
    ~FList() {

        FBlock<T>* read = this->head;
        FBlock<T>* read_next = nullptr;
        while (read != nullptr) {
            read_next = read->next;
            delete read;
            read = read_next;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->total_length = 0;

        //set flag
        this->defragmented = true;
    }

#ifdef FDEBUG
    /// <summary>
    /// Display the (hidden) structure of the FList (using std::cout).
    /// </summary>
    /// <returns>void</returns>
    void print_structure() const {
        FBlock<T>* read = head;
        std::cout << '{';
        std::cout << this->total_length << ':';
        while (read != nullptr) {
            std::cout << '[';
            std::cout << '<' << read->start_indx << ':';
            std::cout << read->block_size << '>';
            for (fuint i = 0; i < read->block_size; i++) {
                std::cout << '(' << read->block[i] << ')';
            }
            std::cout << ']';
            read = read->next;
        }
        std::cout << '}';
        if (!this->defragmented) {
            std::cout << 'F';
        }
        else {
            std::cout << "DF";
        }
        std::cout << std::endl;
    }
#endif

};

//some quality of life typedefs :-)
typedef FList<int> FInts;
typedef FList<float> FFloats;
typedef FList<double> FDoubles;
typedef FList<bool> FBools;
}
#endif