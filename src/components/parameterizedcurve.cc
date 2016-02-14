#include "parameterizedcurve.h"

namespace Xi {

void Parameterized_Curve::update_logic(const Update_Details &ud)
{
  auto next_time_elpased = update_time_elpased + ud.delta_time_elpased;
  if (next_time_elpased > update_parameter.duration)
  {
    switch (update_parameter.update_complete_policy)
    {
    case UCP_Stay:
      return;
    case UCP_Stop:
      position_value = 0;
      velocity_value = 0;
      return;
    case UCP_Reset:
      next_time_elpased = 0;
      // fall through.
    case UCP_Continue:
      break;
    }
  }

  update_time_elpased = next_time_elpased;

  auto res = update_parameter.update_function(update_time_elpased,
                                              update_parameter.duration,
                                              update_parameter.change_value);

  position_value = res.x;
  position_value=  res.y;
}



} // namespace Xi

