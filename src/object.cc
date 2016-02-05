#include "object.h"

namespace Xi {

// {{{ Object
Object::~Object() { }

void Object::initialize() { }

void Object::finalize() { }

// }}}


// {{{ Cloneable_Object
Object *Cloneable_Object::clone() const
{
  return nullptr;
}
// }}}


// {{{ Pooled_Object

void Pooled_Object::finalize()
{
  delete this;
}

Pooled_Object::~Pooled_Object()
{
  Xi_debug_check(ref_count == 0);
}

// }}}

} // namespace Xi

