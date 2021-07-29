#ifndef ONCE_FMACROS_H
#define ONCE_FMACROS_H

//symbols
//#define DEBUG_MODE //enables structure printing
#define OSTREAM_OPS //enables << operator

//macros
#define UINT unsigned __int32
#define NULLP nullptr

//dependancies - try to keep as minimal as possible
#include <stdexcept>

//debug dependencies
#ifdef DEBUG_MODE
#include <iostream>
#endif

//ostream operations dependancies
//optional to keep actual distribution minimal
#ifdef OSTREAM_OPS
#include <iostream>
#endif

#endif