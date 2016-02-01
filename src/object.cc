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


// {{{ Ref_Counted_Object

void Ref_Counted_Object::finalize()
{
  delete this;
}

Ref_Counted_Object::~Ref_Counted_Object()
{
  Xi_debug_check(ref_count == 0);
}

// }}}

} // namespace Xi

