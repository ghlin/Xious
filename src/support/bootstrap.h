#ifndef BOOTSTRAP_H_INCLUDED_79FKHBZU
#define BOOTSTRAP_H_INCLUDED_79FKHBZU

#include "../config.h"
#include "init.h"

namespace Xi { namespace init {

using Bootstrap_Task = std::function<void ( const Str_List & /* from argc & argv */
                                          , const Str      & /* path */
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

attr_export void    bootstrap_finalize();

} // namespace init
} // namespace Xi

#define XI_INIT_PRIO_BOOTSTRAP (XI_INIT_PRIO_INTERNAL + 100)

#define XI_BOOTSTRAP_SCOPE()                              \
  namespace {                                             \
  namespace XI_JOIN(bootstrap_scope_, __LINE__) {         \
  static attr_ctrl(spec_visisbility_hidden,               \
                   constructor(XI_INIT_PRIO_BOOTSTRAP))   \
  void bootstrap(); } }                                   \
  void XI_JOIN(bootstrap_scope_, __LINE__)::bootstrap()

#define XI_BOOTSTRAP_ON(path, deps)                            \
  namespace {                                                  \
  namespace XI_JOIN(bootstrap_add_task_, __LINE__) {           \
  static void bootstrap_task(const Str_List &,                 \
                             const Str &);                     \
  } }                                                          \
  XI_BOOTSTRAP_SCOPE()                                         \
  {                                                            \
    ::Xi::init::bootstrap_add_task(                            \
      path, deps,                                              \
      XI_JOIN(bootstrap_add_task_, __LINE__)::bootstrap_task); \
  }                                                            \
  void XI_JOIN(bootstrap_add_task_, __LINE__)::bootstrap_task( \
    attr_unused const Str_List &$args,                         \
    attr_unused const Str &$path)

#define XI_BOOTSTRAP_CLEANUP(path, deps)                       \
  namespace {                                                  \
  namespace XI_JOIN(bootstrap_add_task_, __LINE__) {           \
  static void bootstrap_task(const Str_List &,                 \
                             const Str &);                     \
  } }                                                          \
  XI_BOOTSTRAP_SCOPE()                                         \
  {                                                            \
    ::Xi::init::bootstrap_add_cleanup(                         \
      path, deps,                                              \
      XI_JOIN(bootstrap_add_task_, __LINE__)::bootstrap_task); \
  }                                                            \
  void XI_JOIN(bootstrap_add_task_, __LINE__)::bootstrap_task( \
    attr_unused const Str_List &$args,                         \
    attr_unused const Str &$path)


#endif // end of include guard: BOOTSTRAP_H_INCLUDED_79FKHBZU

