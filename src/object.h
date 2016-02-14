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
  virtual Handle<Prototype> clone() const;

  virtual Handle<Prototype> share() const
  {
    return clone();
  }
};

#define XI_STATELESS(Type)                                     \
  virtual Handle<Prototype> share() const override final;      \
  {                                                            \
    static_assert(std::is_final<Type>::value,                  \
                  "A Stateless object must be Final.");        \
    return handle_cast<Prototype>(const_cast<Type &>(*this));  \
  }


#define XI_COPY_CLONE(Type)                           \
  virtual Handle<Prototype> clone() const override    \
  {                                                   \
    return std::make_shared<Type>(*this);             \
  }

} // namespace Xi

#endif // end of include guard: OBJECT_H_INCLUDED_REVFSI2K

