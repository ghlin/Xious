#ifndef OBJECT_H_INCLUDED_REVFSI2K
#define OBJECT_H_INCLUDED_REVFSI2K

#include "config.h"
#include "variant.h"
#include "property.h"

namespace Xi {

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

