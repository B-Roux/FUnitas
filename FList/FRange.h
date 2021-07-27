#ifndef ONCE_FRANGE_H
#define ONCE_FRANGE_H

#include "FMacros.h"

struct FRange {
	UINT start;
	UINT end;

	FRange(UINT start_, UINT end_) {
		this->start = start_;
		this->end = end_;
	}
};

#endif