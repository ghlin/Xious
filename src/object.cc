#include "object.h"

namespace Xi {

// {{{ Object
Object::~Object() { }

void Object::initialize() { }

void Object::finalize() { }

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

