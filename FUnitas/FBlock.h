#ifndef ONCE_FBLOCK_H
#define ONCE_FBLOCK_H

#include "FMacros.h"

FNAMESPACE {

template <typename T> struct FBlock {
    T* block;
    FBlock<T>* next;
    FBlock<T>* prev;
    FUINT block_size;
    FUINT start_indx;

    /// <summary>
    /// Initialize the FBlock.
    /// </summary>
    /// <returns>FBlock<T></returns>
    FBlock(T* block, FUINT block_size, FUINT start_indx) {
        this->block = block;
        this->block_size = block_size;
        this->start_indx = start_indx;
        this->next = FNULLP;
        this->prev = FNULLP;
    }

    /// <summary>
    /// Deconstruct the FBlock.
    /// Do not use this if you don't have a very good reason to.
    /// </summary>
    /// <returns>void</returns>
    ~FBlock() {
        delete[] this->block;
        this->block_size = 0;
        this->start_indx = 0;
    }
};

}
#endif