#include "movement.h"

// @@@ compile: -E
// @@@ output: /tmp/mm.i

namespace Xi {

XIC_COMPLETE(Movement, f, change_value, duration, limit_value)
XIC_COMPLETE(Movement, u, curve_type, finish_policy)

Phy_Status Movement::do_update(const Update_Details &)
{
  // TODO(ghlin) : reminder 2016-02-07 14:12:02
  return { };
}

} // namespace Xi

