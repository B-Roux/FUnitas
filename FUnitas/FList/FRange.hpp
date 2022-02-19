#ifndef ONCE_FRANGE_HPP
#define ONCE_FRANGE_HPP

#include "../FMacros.hpp"

FNAMESPACE {

struct FRange {
    fuint start;
    fuint end;
    int by;

    /// <summary>
    /// Initialize the FRange.
    /// </summary>
    /// <returns>FRange</returns>
    FRange(fuint start, fuint end) {
        this->start = start;
        this->end = end;

        //if no explicit 'by' is given, assume 1
        this->by = 1;
    }

    /// <summary>
    /// Initialize the FRange.
    /// </summary>
    /// <returns>FRange</returns>
    FRange(fuint start, fuint end, int by) {

        //'by' must be able to accept neg vals
        //check for 'by 0' error
        if (by == 0) throw std::out_of_range("'by' cannot be 0");

        //otherwise just assign normally
        this->start = start;
        this->end = end;
        this->by = by;
    }
};

}
#endif
