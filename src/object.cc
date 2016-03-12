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

Str Object::dump_inheritance_chain() const
{
  return "[Object]";
}

Handle<Prototype> Prototype::clone() const
{
  Xi_die("Clone not impl...");

  return nullptr;
}

} // namespace Xi

