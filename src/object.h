#ifndef OBJECT_H_INCLUDED_REVFSI2K
#define OBJECT_H_INCLUDED_REVFSI2K

#include "config.h"
#include "variant.h"
#include "property.h"
#include "support/chain.h"

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
  virtual Str dump_classname() const = 0;
  virtual Str dump_inheritance_chain() const;
};


class Prototype : public Object
{
public:
  virtual Handle<Prototype> clone() const;
};

template <class S, class With>
class Enable_Clone_Via_CCTOR : public S
{
debug_or_protect:
  using Super = S;
public:
  using Super::Super;

  virtual Handle<Prototype> clone() const override
  {
    static_assert(std::is_base_of<Prototype, Enable_Clone_Via_CCTOR>::value, "Inherit Prototype first!");

    using Client = typename With::Client;

    return make_handle<Client>(*static_cast<const Client *>(this));
  }
};

template <class S, class With>
class Enable_Dump_By_Type : public S
{
  static const Str &classname()
  {
    using Client = typename With::Client;

    static Str the_classname = u_pretty_typename<Client>();

    return the_classname;
  }
debug_or_protect:
  using Super = S;
public:
  using Super::Super;

public:
  virtual Str dump_classname() const override
  {
    return classname();
  }

  virtual Str dump_inheritance_chain() const override
  {
    return dump_inheritance_chain() + " -> " + classname();
  }
};

template <class B>
using Extends = chain<With<B>>;

template <class With, class ...R>
using Implements = chain
                   < With
                   , R...
                   , addin<Enable_Dump_By_Type>
                   , addin<Enable_Clone_Via_CCTOR>
                   >;

} // namespace Xi

#endif // end of include guard: OBJECT_H_INCLUDED_REVFSI2K

