#include "windy.h"

namespace Xi {

XIC_COMPLETE(Windy, v, wind_dir)

Phy_Status Windy::do_update(const Update_Details &ud)
{
  XI_UNUSED(ud);

  return { { }, wind_dir };
}


} // namespace Xi
