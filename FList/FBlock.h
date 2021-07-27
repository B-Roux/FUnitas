#ifndef ONCE_FBLOCK_H
#define ONCE_FBLOCK_H

#include "FMacros.h"

template <typename T> struct FBlock {
	T* block;
	FBlock<T>* next;
	FBlock<T>* prev;
	UINT block_size;
	UINT start_indx;

	FBlock (T* block_, UINT block_size_, UINT start_indx_) {
		this->block = block_;
		this->block_size = block_size_;
		this->start_indx = start_indx_;
		this->next = NULLP;
		this->prev = NULLP;
	}

	~FBlock() {
		delete[] this->block;
		this->block_size = 0;
		this->start_indx = 0;
	}
};

#endif