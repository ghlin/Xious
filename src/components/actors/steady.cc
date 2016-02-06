#include "steady.h"

namespace Xi {

XIC_COMPLETE(Steady, v, at)

Phy_Status Steady::do_update(const Update_Details &ud)
{
  XI_UNUSED(ud);

  return { at, { } };
}


} // namespace Xi

