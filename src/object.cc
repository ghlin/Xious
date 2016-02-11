#include "object.h"

namespace Xi {

Object::~Object()
{
}

Var Object::get_property(const Str &) const
{
  return { };
}

void Object::set_property(const Str &, const Var &)
{
  return;
}

} // namespace Xi

