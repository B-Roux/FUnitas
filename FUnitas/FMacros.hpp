#ifndef ONCE_FMACROS_H
#define ONCE_FMACROS_H

// Think of this as a config file

//symbols
#define FDEBUG //enables structure printing
#define FIOSTREAM //enables stream compatibility
#define FINIT_LIST //enables nicer initializations

//expressions

#define FNAMESPACE namespace funitas

//dependancies - try to keep as minimal as possible
#include <stdexcept>

//Conditional dependencies
#ifdef FDEBUG
#include <iostream>
#endif

#ifdef FIOSTREAM
#include <iostream>
#endif

#ifdef FINIT_LIST
#include <initializer_list>
#endif

//in-namespace definitions
FNAMESPACE{
    typedef  unsigned __int32 fuint;
}
#endif