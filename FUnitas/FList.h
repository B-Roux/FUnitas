#ifndef ONCE_FLIST_H
#define ONCE_FLIST_H

#include "FMacros.h"
#include "FBlock.h"
#include "FRange.h"

template <typename T> class FList {

private:
	FBlock<T>* head;
	FBlock<T>* tail;
	UINT total_length;

public:

	//BASIC OPPERATORS

	void append (const FList<T>& op) { //Does not return new allocation
		//Add an FList to this one without affecting one being added
		this->_integrate_array(op._export_array(), op.length());
	}
	void append (const T op) { //Does not return new allocation
		//Add a T to this FList without affecting one being added
		T* buffer = new T[1];
		buffer[0] = op;
		this->_integrate_array(buffer, 1);
	}

	T& operator [] (const UINT idx) const {
		//Get a reference to a specific item by index
		FBlock<T>* read = tail;
		if ((idx >= this->total_length) || (idx < 0)) {
			throw std::out_of_range("Index out of Bounds");
		}
		while (read != NULLP) {
			if (idx < read->start_indx) {
				read = read->prev;
			}
			else {
				return read->block[idx - read->start_indx];
			}
		}
		throw std::out_of_range("Index out of Bounds");
	}

	FList<T> operator [] (const FRange idx) const { //Returns new allocation
		//Get the sub-array starting at FRange.start and ending at FRange.end or FList.length()-1
		UINT start = idx.start;
		UINT end = (idx.end <= this->total_length) ? idx.end : this->total_length;

		if ((start >= this->total_length) || (start > end)) {
			throw std::out_of_range("Index out of Bounds");
		}

		T* buffer = new T[end - start];
		FBlock<T>* read = head;
		UINT j = 0;
		UINT k = 0;
		while (read != NULLP) {
			//i: loop through the data block
			//j: loop through this FList
			//k: loop through the range
			for (UINT i = 0; i < read->block_size; i++) {
				if ((j >= start) && (j < end)) {
					buffer[k] = read->block[i];
					++k;
				}
				++j;
			}
			read = read->next;
		}

		return FList<T>(buffer, end - start);
	}

	FList<T> operator [] (const FList<bool> &logical) const { //Returns new allocation
		// returns all this[i] where logical[i]
		if (logical.length() != this->total_length) {
			throw std::out_of_range("Dimensional Mismatch");
		}

		UINT n_true = 0;

		for (UINT i = 0; i < logical.length(); i++) {
			if (logical[i]) {
				++n_true;
			}
		}
		if (n_true > 0) {
			T* buffer = new T[n_true];
			for (UINT i = 0, j = 0; i < logical.length(); i++) {
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

	void operator = (const FList<T> &op) {

		//release currently held memory
		FBlock<T>* read = this->head;
		FBlock<T>* read_next = NULLP;
		while (read != NULLP) {
			read_next = read->next;
			delete read;
			read = read_next;
		}

		//reset internal state
		this->head = NULLP;
		this->tail = NULLP;
		this->total_length = 0;

		//instantiate from op
		this->_integrate_array(op._export_array(), op.length());
	}

	//COMPARISON OPERATORS

	//element-wise greater than
	FList<bool> operator > (const FList<T>& op) const {
		if (op.length() != this->total_length) {
			throw std::out_of_range("Dimensional Mismatch");
		}

		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] > op[j];
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}
	FList<bool> operator > (const T& op) const {
		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] > op;
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}

	//element-wise less than
	FList<bool> operator < (const FList<T>& op) const {
		if (op.length() != this->total_length) {
			throw std::out_of_range("Dimensional Mismatch");
		}

		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] < op[j];
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}
	FList<bool> operator < (const T& op) const {
		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] < op;
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}

	//element-wise greater than or equal
	FList<bool> operator >= (const FList<T>& op) const {
		if (op.length() != this->total_length) {
			throw std::out_of_range("Dimensional Mismatch");
		}

		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] >= op[j];
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}
	FList<bool> operator >= (const T& op) const {
		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] >= op;
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}

	//element-wise less than or equal
	FList<bool> operator <= (const FList<T>& op) const {
		if (op.length() != this->total_length) {
			throw std::out_of_range("Dimensional Mismatch");
		}

		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] <= op[j];
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}
	FList<bool> operator <= (const T& op) const {
		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] <= op;
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}

	//element-wise equal
	FList<bool> operator == (const FList<T>& op) const {
		if (op.length() != this->total_length) {
			throw std::out_of_range("Dimensional Mismatch");
		}

		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] == op[j];
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}
	FList<bool> operator == (const T& op) const {
		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] == op;
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}

	//element-wise not equal
	FList<bool> operator != (const FList<T>& op) const {
		if (op.length() != this->total_length) {
			throw std::out_of_range("Dimensional Mismatch");
		}

		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] != op[j];
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}
	FList<bool> operator != (const T& op) const {
		bool* buffer = new bool[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i] != op;
				++j;
			}
			read = read->next;
		}

		return FList<bool>(buffer, this->total_length);
	}

	//MISCILLANEOUS OPERATORS (FRIEND FUNCTIONS)
#ifdef OSTREAM_OPS
	friend std::ostream& operator<<(std::ostream& os, FList<T> list) {
		os << "[";
		for (UINT i = 0; i < list.length(); i++) {
			if (i > 0) {
				os << ", ";
			}
			os << list[i];
		}
		os << "]";
		return os;
	}
#endif

	//ATTRIBUTE GETTERS & SETTERS

	UINT length() const {
		//get the length of the FList
		return this->total_length;
	}

	void _integrate_array(T* block, const UINT length) {
		//Take a DA array pointer and use it as a data block WITHOUT NEW ALLOCATION.
		//When using this function, the caller gives up responsibility of the data allocation
		//This is an internal function and its functionality must be hidden from the caller
		if (head == NULLP) {
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

	T* _export_array() const { //Returns new allocation
		//Return a pointer to a NEWLY ALLOCATED DA array that contains all elements
		//When using this function, the caller assumes responsibility of the data allocation
		//This is an internal function and its functionality must be hidden from the caller
		T* buffer = new T[this->total_length];
		FBlock<T>* read = this->head;
		UINT j = 0;
		while (read != NULLP) {
			for (UINT i = 0; i < read->block_size; i++) {
				buffer[j] = read->block[i];
				++j;
			}
			read = read->next;
		}
		return buffer;
	}

	//CONSTRUCTORS & DECONSTRUCTORS

	FList<T>() {
		//Default constructor
		this->head = NULLP;
		this->tail = NULLP;
		this->total_length = 0;
	}

	FList<T>(T* block, UINT length) {
		//Parameterized constructor
		//When using this function, the caller gives up responsibility of the data allocation
		this->head = new FBlock<T>(block, length, 0);
		this->tail = this->head;
		this->total_length = length;
	}

	FList<T>(const FList<T>& old) {
		//deep copy constructor
		this->head = new FBlock<T>(old._export_array(), old.length(), 0);
		this->tail = this->head;
		this->total_length = old.length();
	}
	
	~FList() {
		//deconstructor
		FBlock<T>* read = this->head;
		FBlock<T>* read_next = NULLP;
		while (read != NULLP) {
			read_next = read->next;
			delete read;
			read = read_next;
		}
		this->head = NULLP;
		this->tail = NULLP;
		this->total_length = 0;
	}

#ifdef DEBUG_MODE
	void print_structure() const {
		FBlock<T>* read = head;
		std::cout << '{';
		std::cout << this->total_length << ':';
		while (read != NULLP) {
			std::cout << '[';
			std::cout << '<' << read->start_indx << ':';
			std::cout << read->block_size << '>';
			for (UINT i = 0; i < read->block_size; i++) {
				std::cout << '(' << read->block[i] << ')';
			}
			std::cout << ']';
			read = read->next;
		}
		std::cout << '}' << std::endl;
	}
#endif

};

#endif