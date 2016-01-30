#ifndef CONFIG_H_INCLUDED_YRWXK8F1
#define CONFIG_H_INCLUDED_YRWXK8F1

#include "common/base.h"
#include "fwd.h"

#define XI_DEBUG_MODE   1
#define XI_RELEASE_MODE 0

#if defined(DEBUG) || !defined(RELEASE)
#define XI_DEBUG   1
#define XI_MODE    XI_DEBUG_MODE
#else
#define XI_RELEASE 1
#define XI_MODE    XI_RELEASE_MODE
#endif

#endif // end of include guard: CONFIG_H_INCLUDED_YRWXK8F1

