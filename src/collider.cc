#include "collider.h"

namespace Xi {

bool Collider::special_colliding_logic(const vec_t &,
                                       const Collider *,
                                       const vec_t &) const
{
  Xi_die("special_colliding_logic not impl...");

  return false;
}

} // namespace Xi

