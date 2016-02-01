#ifndef BOOTSTRAP_H_INCLUDED_79FKHBZU
#define BOOTSTRAP_H_INCLUDED_79FKHBZU

#include "../config.h"
#include "init.h"

namespace Xi { namespace init {


/**
 * 取得初始化模块的根节点.
 *
 * \note 不要把根节点注册到其他Init_root上.
 */
attr_export Init_Group *bootstrap_root();

/**
 * 执行初始化动作.
 */
attr_export void      bootstrap_initialize();

/**
 * 执行注销动作, 并销毁bootstrap根.
 */
attr_export void      bootstrap_finalize();

} // namespace init
} // namespace Xi

#define attr_bootstrap attr_init(XI_INIT_PRIO_INTERNAL + 1000)

#define XI_BOOTSTRAP_REGISTER(name, ...)                \
  namespace XI_JOIN(bootstrap_register_, name) {        \
    attr_bootstrap void do_register()                   \
    {                                                   \
      ::Xi::init::bootstrap_root()->register_node(      \
        ::Xi::init::make_init_node(                     \
          XI_STRINGIFY(name), __VA_ARGS__));            \
    } }

#define XI_BOOTSTRAP_REGISTER_CLASS(Klass)                \
  namespace XI_JOIN(bootstrap_register_, Klass) {         \
    attr_bootstrap void do_register()                     \
    {                                                     \
      ::Xi::init::bootstrap_root()->register_node(        \
        new Klass);                                       \
    } }

#define XI_BOOTSTRAP_REGISTER_INIT(name, ...)             \
  namespace XI_JOIN(bootstrap_register_, name) {          \
    void _initializer(Xi::init::Init_Node *node);         \
    attr_bootstrap void do_register()                     \
    {                                                     \
      ::Xi::init::bootstrap_root()->register_node(        \
        ::Xi::init::make_init_node(                       \
                                XI_STRINGIFY(name),       \
                                __VA_ARGS__,              \
                                &_initializer)); } }      \
  void XI_JOIN(bootstrap_register_, name)::               \
    _initializer(attr_unused Xi::init::Init_Node *self)

#endif // end of include guard: BOOTSTRAP_H_INCLUDED_79FKHBZU

