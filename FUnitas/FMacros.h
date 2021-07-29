#ifndef ONCE_FMACROS_H
#define ONCE_FMACROS_H

//symbols
//#define FDEBUG //enables structure printing
#define FIOSTREAM //enables << operator

//macros
#define FUINT unsigned __int32
#define FNULLP nullptr

#define FNAMESPACE_BEGIN namespace ftd {
#define FNAMESPACE_END }

//dependancies - try to keep as minimal as possible
#include <stdexcept>

//debug dependencies
#ifdef FDEBUG
#include <iostream>
#endif

//ostream operations dependancies
//optional to keep actual distribution minimal
#ifdef FIOSTREAM
#include <iostream>
#endif

#endif