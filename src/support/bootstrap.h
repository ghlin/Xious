#ifndef BOOTSTRAP_H_INCLUDED_79FKHBZU
#define BOOTSTRAP_H_INCLUDED_79FKHBZU

#include "../config.h"
#include "init.h"

namespace Xi { namespace init {

using Bootstrap_Task = std::function<void ( int             /* argc */
                                          , const char **   /* argv */
                                          , const Str &     /* path */
                                          )>;

attr_export void    bootstrap_add_task(const Str      &path,
                                       const Str_List &deps,
                                       Bootstrap_Task  task);

attr_export void    bootstrap_add_post_task(const Str      &path,
                                            const Str_List &deps,
                                            Bootstrap_Task  task);

attr_export void    bootstrap_add_cleanup(const Str          &path,
                                          const Str_List     &deps,
                                          Bootstrap_Task      task);

attr_export void    bootstrap_initialize(int argc, const char **argv);

attr_export void    bootstrap_finalize(int argc, const char **argv);

} // namespace init
} // namespace Xi

#define XI_INIT_PRIO_BOOTSTRAP (XI_INIT_PRIO_INTERNAL + 100)

#define XI_BOOTSTRAP_SCOPE() \
  namespace { namespace bootstrap_scope { \
  static attr_ctrl(spec_visisbility_hidden, \
                   constructor(XI_INIT_PRIO_BOOTSTRAP)) \
  void entry(); } } \
  void bootstrap_scope::entry()

#endif // end of include guard: BOOTSTRAP_H_INCLUDED_79FKHBZU

