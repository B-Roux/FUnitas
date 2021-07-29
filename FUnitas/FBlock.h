#ifndef ONCE_FBLOCK_H
#define ONCE_FBLOCK_H

#include "FMacros.h"

FNAMESPACE_BEGIN

template <typename T> struct FBlock {
	T* block;
	FBlock<T>* next;
	FBlock<T>* prev;
	FUINT block_size;
	FUINT start_indx;

	FBlock (T* block_, FUINT block_size_, FUINT start_indx_) {
		this->block = block_;
		this->block_size = block_size_;
		this->start_indx = start_indx_;
		this->next = FNULLP;
		this->prev = FNULLP;
	}

	~FBlock() {
		delete[] this->block;
		this->block_size = 0;
		this->start_indx = 0;
	}
};

FNAMESPACE_END
#endif