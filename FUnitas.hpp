#ifndef ONCE_FUNITAS_MAIN_HPP
#define ONCE_FUNITAS_MAIN_HPP

/*
 * In this file, expose all of the functionality you
 * would want end users to interact with.
 *
 * This file is basically an import aggregate so that you
 * only ever have to include this in a project.
 */

// Core FUnitas datastructure, must be included first
#include "FUnitas/FList/FList.hpp"

//undefine all FMacros (so they don't mess other things up):

//symbols
#undef FDEBUG
#undef FIOSTREAM
#undef FINIT_LIST

//expressions
#undef FNAMESPACE

#endif
