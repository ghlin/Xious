#ifndef BOOTSTRAP_H_INCLUDED_79FKHBZU
#define BOOTSTRAP_H_INCLUDED_79FKHBZU

#include "../config.h"
#include "init.h"

namespace Xi { namespace init {

attr_export Init_Mgr *bootstrap_mgr();

} // namespace init
} // namespace Xi

#define XI_BOOTSTRAP_REGISTER(name, ...)             \
  namespace XI_JOIN(bootstrap_register_, name) {     \
    attr_init_routine void do_register()             \
    {                                                \
      ::Xi::init::bootstrap_mgr()->register_module(  \
        ::Xi::init::make_module(name, __VA_ARGS__)); \
    } }

#define XI_BOOTSTRAP_REGISTER_CLASS(Klass)           \
  namespace XI_JOIN(bootstrap_register_, Klass) {    \
    attr_init_routine void do_register()             \
    {                                                \
      ::Xi::init::bootstrap_mgr()->register_module(  \
        new Klass);                                  \
    } }

#define XI_BOOTSTRAP_REGISTER_INIT(name, ...)        \
  namespace XI_JOIN(bootstrap_register_, name) {     \
    void _initializer(Xi::init::Module *module);     \
    attr_init_routine void do_register()             \
    {                                                \
      ::Xi::init::bootstrap_mgr()->register_module(  \
        ::Xi::init::make_module(name,                \
                                __VA_ARGS__,         \
                                &_initializer); } }  \
  void XI_JOIN(bootstrap_register_, name)::          \
    _initializer(attr_unused Xi::init::Module *self)

#endif // end of include guard: BOOTSTRAP_H_INCLUDED_79FKHBZU

