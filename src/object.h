#ifndef OBJECT_H_INCLUDED_REVFSI2K
#define OBJECT_H_INCLUDED_REVFSI2K

#include "config.h"
#include "variant.h"
#include "property.h"
#include "util/chain.h"

namespace Xi {

class Object_Property_Ctrl;

class Object
  : public std::enable_shared_from_this<Object>
  /* TODO: enable_shared_from_this -> Shared_Handle */
{
  friend class Object_Property_Ctrl;
public:
  virtual ~Object() = 0;

protected:
  virtual Var  get_property(const Str &key) const;
  virtual void set_property(const Str &key, const Var &val);

  // debug
  virtual Str dump_classname() const;
};


class Prototype : public Object
{
public:
  virtual Handle<Prototype> clone() const;
};

namespace addon { namespace details {

template <class B, class D>
class Addon_Dump_Classname : public B
{
public:
  using B::B;

  virtual Str dump_classname() const override
  {
    return u_pretty_typename<D>();
  };
};

template <class B, class D>
class Addon_Clone_Via_CCTOR : public B
{
public:
  using B::B;

  virtual Handle<Prototype> clone() const override
  {
    return make_handle<D>(*static_cast<const D *>(this));
  }
};

} // namespace details

using Dump_Classname  = Make_Addon<details::Addon_Dump_Classname>;
using Clone_Via_CCTOR = Make_Addon<details::Addon_Clone_Via_CCTOR>;

} // namespace addon


template <class B>
using Extends = chain<With<B, /* doesn't matter */ void>>;

template <class B, class D>
using Implements = chain<With<B, D>, addon::Dump_Classname, addon::Clone_Via_CCTOR>;

} // namespace Xi

#endif // end of include guard: OBJECT_H_INCLUDED_REVFSI2K

