#ifndef ONCE_FRANGE_H
#define ONCE_FRANGE_H

#include "../FMacros.hpp"

FNAMESPACE {

struct FRange {
    fuint start;
    fuint end;

    /// <summary>
    /// Initialize the FRange.
    /// </summary>
    /// <returns>FRange</returns>
    FRange(fuint start, fuint end) {
        this->start = start;
        this->end = end;
    }
};

}
#endif