#ifndef OBJECT_H_INCLUDED_REVFSI2K
#define OBJECT_H_INCLUDED_REVFSI2K

#include "config.h"
#include "variant.h"

namespace Xi {

#define _XI_PROP_DECL(Key, name)                                 \
  constexpr static char XI_JOIN(Prop_, Key)[] = XI_STRINGIFY(Key)

#define _XI_PROP_GET_IMPL(Key, name)                      \
  do {                                                    \
    if (key == XI_STRINGIFY(Key))                         \
      return Var::of<std::decay_t<decltype(name)>>(name); \
  } while (false)

#define _XI_PROP_SET_IMPL(Key, name)                  \
  do {                                                \
    if (key == XI_STRINGIFY(Key))                     \
    {                                                 \
      name = val.get<std::decay_t<decltype(name)>>(); \
      return;                                         \
    }                                                 \
  } while (false)

#define _XI_PROP_DECL_HELPER(x)     _XI_PROP_DECL x
#define _XI_PROP_GET_IMPL_HELPER(x) _XI_PROP_GET_IMPL x
#define _XI_PROP_SET_IMPL_HELPER(x) _XI_PROP_SET_IMPL x

#define XI_PROP_DECL(...)     XI_FOREACH(_XI_PROP_DECL_HELPER, ;, __VA_ARGS__)
#define XI_PROP_SET_IMPL(...) XI_FOREACH(_XI_PROP_SET_IMPL_HELPER, ;, __VA_ARGS__)
#define XI_PROP_GET_IMPL(...) XI_FOREACH(_XI_PROP_GET_IMPL_HELPER, ;, __VA_ARGS__)

#define _XI_PROP_MARK_OVERRIDE_GET() virtual Var get_property(const Str &key) const override
#define _XI_PROP_MARK_OVERRIDE_SET() virtual void set_property(const Str &key, const Var &val) override

#define XI_PROP_IMPL_GET_BEGIN() _XI_PROP_MARK_OVERRIDE_GET()  {
#define XI_PROP_IMPL_SET_BEGIN() _XI_PROP_MARK_OVERRIDE_SET()  {

#define XI_PROP_IMPL_GET_END() return Super::get_property(key); }
#define XI_PROP_IMPL_SET_END() return Super::set_property(key, val); }

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

class Object_Property_Ctrl;

class Object : public std::enable_shared_from_this<Object>
{
  friend class Object_Property_Ctrl;
public:
  virtual ~Object() = 0;

protected:
  virtual Var  get_property(const Str &key) const;
  virtual void set_property(const Str &key, const Var &val);
};


class Prototype : public Object
{
public:
  virtual Handle<Prototype> clone() const = 0;
};

#define XI_SHARE_CLONE(Type)                          \
  virtual Handle<Prototype> clone() const override    \
  {                                                   \
    return std::static_pointer_cast<Prototype>(       \
      const_cast<Object *>(this)->share_from_this()); \
  }

#define XI_COPY_CLONE(Type)                           \
  virtual Handle<Prototype> clone() const override    \
  {                                                   \
    return new Type(*this);                           \
  }

} // namespace Xi

#endif // end of include guard: OBJECT_H_INCLUDED_REVFSI2K

