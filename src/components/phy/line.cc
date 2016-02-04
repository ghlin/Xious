#include "line.h"

namespace Xi {

Phy_Status Line::do_update(const Xi::Update_Details &ud)
{
  return { end_point.position * time_elpased / time, end_point.velocity / time };
}

} // namespace Xi

