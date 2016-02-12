#ifndef PROPERTY_H_INCLUDED_0CKF8BJA
#define PROPERTY_H_INCLUDED_0CKF8BJA

#define _XI_PROP_DECL(Key, expr) constexpr static char XI_JOIN(Prop_, Key)[] = XI_STRINGIFY(Key)

#define _XI_PROP_GET_IMPL_RW(Key, expr)                   \
  do {                                                    \
    if ($key == XI_STRINGIFY(Key))                        \
      return Var::of<std::decay_t<decltype(expr)>>(expr); \
  } while (false)
#define _XI_PROP_GET_IMPL_RO(Key, expr) _XI_PROP_GET_IMPL_RW(Key, expr)
#define _XI_PROP_GET_IMPL_WO(Key, expr)                           \
  do {                                                            \
    if ($key == XI_STRINGIFY(Key))                                \
      Xi_die("Property `" XI_STRINGIFY(Key) "' cannot be read."); \
  } while (false)

#define _XI_PROP_SET_IMPL_RW(Key, expr)                \
  do {                                                 \
    if ($key == XI_STRINGIFY(Key))                     \
    {                                                  \
      expr = $val.get<std::decay_t<decltype(expr)>>(); \
      return;                                          \
    }                                                  \
  } while (false)
#define _XI_PROP_SET_IMPL_SETTER_EXP(Key, expr)        \
  do {                                                 \
    if ($key == XI_STRINGIFY(Key))                     \
    {                                                  \
      expr;                                            \
      return;                                          \
    }                                                  \
  } while (false)
#define _XI_PROP_SET_IMPL_WO(Key, expr) _XI_PROP_SET_IMPL_RW(Key, expr)
#define _XI_PROP_SET_IMPL_RO(Key, expr)                              \
  do {                                                               \
    if ($key == XI_STRINGIFY(Key))                                   \
      Xi_die("Property `" XI_STRINGIFY(Key) "' cannot be written."); \
  } while (false)

#define _XI_PROP_DECL_HELPER(...) _XI_PROP_DECL(XI_CAR(__VA_ARGS__), XI_CAR(XI_CDR(__VA_ARGS__)))

#define _XI_PROP_GET_IMPL_2(Key, expr)            _XI_PROP_GET_IMPL_RW(Key, expr)
#define _XI_PROP_GET_IMPL_3(Key, expr, opt)       XI_JOIN(_XI_PROP_GET_IMPL_, opt)(Key, expr)
#define _XI_PROP_GET_IMPL_4(Key, expr, opt, ext)  _XI_PROP_GET_IMPL_3(Key, expr, opt)

#define _XI_PROP_SET_IMPL_2(Key, expr)              _XI_PROP_SET_IMPL_RW(Key, expr)
#define _XI_PROP_SET_IMPL_3(Key, expr, opt)         XI_JOIN(_XI_PROP_SET_IMPL_, opt)(Key, expr)
#define _XI_PROP_SET_IMPL_4(Key, expr, opt, ext)    _XI_PROP_SET_IMPL_SETTER_EXP(Key, expr)

#define _XI_PROP_GET_IMPL_HELPER(...) XI_JOIN(_XI_PROP_GET_IMPL_, XI_NARGS(__VA_ARGS__))(__VA_ARGS__)
#define _XI_PROP_SET_IMPL_HELPER(...) XI_JOIN(_XI_PROP_SET_IMPL_, XI_NARGS(__VA_ARGS__))(__VA_ARGS__)

#define _XI_PROP_DECL_FWD(x)     _XI_PROP_DECL_HELPER x
#define _XI_PROP_GET_IMPL_FWD(x) _XI_PROP_GET_IMPL_HELPER x
#define _XI_PROP_SET_IMPL_FWD(x) _XI_PROP_SET_IMPL_HELPER x

#define XI_PROP_DECL(...)     XI_FOREACH(_XI_PROP_DECL_FWD, ;, __VA_ARGS__)
#define XI_PROP_SET_IMPL(...) XI_FOREACH(_XI_PROP_SET_IMPL_FWD, ;, __VA_ARGS__)
#define XI_PROP_GET_IMPL(...) XI_FOREACH(_XI_PROP_GET_IMPL_FWD, ;, __VA_ARGS__)

#define _XI_PROP_MARK_OVERRIDE_GET() virtual Var get_property(const Str &$key) const override
#define _XI_PROP_MARK_OVERRIDE_SET() virtual void set_property(const Str &$key, const Var &$val) override

#define XI_PROP_IMPL_GET_BEGIN() _XI_PROP_MARK_OVERRIDE_GET()  {
#define XI_PROP_IMPL_SET_BEGIN() _XI_PROP_MARK_OVERRIDE_SET()  {

#define XI_PROP_IMPL_GET_END() return Super::get_property($key); }
#define XI_PROP_IMPL_SET_END() return Super::set_property($key, $val); }

#define XI_PROP_EXPORT(...)        \
protected:                         \
  XI_PROP_IMPL_GET_BEGIN()         \
    XI_PROP_GET_IMPL(__VA_ARGS__); \
  XI_PROP_IMPL_GET_END()           \
  XI_PROP_IMPL_SET_BEGIN()         \
    XI_PROP_SET_IMPL(__VA_ARGS__); \
  XI_PROP_IMPL_SET_END()           \
public:                            \
  XI_PROP_DECL(__VA_ARGS__)


#endif // end of include guard: PROPERTY_H_INCLUDED_0CKF8BJA

