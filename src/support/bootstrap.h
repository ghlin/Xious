#ifndef BOOTSTRAP_H_INCLUDED_79FKHBZU
#define BOOTSTRAP_H_INCLUDED_79FKHBZU

#include "../config.h"
#include "init.h"

namespace Xi { namespace init {

attr_export Handle *bootstrap_root();
attr_export void    bootstrap_initialize();
attr_export void    bootstrap_finalize();

} // namespace init
} // namespace Xi

#define attr_bootstrap attr_init(XI_INIT_PRIO_INTERNAL + 1000)

// TODO(ghlin) : complete 2016-02-02 20:36:34

#endif // end of include guard: BOOTSTRAP_H_INCLUDED_79FKHBZU

