#include "stay.h"

namespace Xi {

Phy_Status Stay::do_update(const Update_Details &)
{
  return { get_stay_at(), { } };
}

} // namespace Xi

