#include "line.h"

namespace Xi {

Phy_Status Line::do_update(const Update_Details &ud)
{
  return
  {
    get_end_point() / get_duration() * get_time_elpased(),
    get_end_point() / get_duration()
  };
}

} // namespace Xi
