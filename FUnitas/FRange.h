#ifndef ONCE_FRANGE_H
#define ONCE_FRANGE_H

#include "FMacros.h"

FNAMESPACE {

struct FRange {
	FUINT start;
	FUINT end;

	FRange(FUINT start, FUINT end) {
		this->start = start;
		this->end = end;
	}
};

}
#endif