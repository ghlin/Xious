#include "parameterized.h"

namespace Xi {

static inline
vec_t update(const Update_Parameter &up, float_t time_elpased)
{
  if (time_elpased > up.duration)
  {
    switch (up.after_policy)
    {
    case AP_Reset:
      return { 0, 0 };
    case AP_Stop:
      return { up.change_value, 0 };
    default:;
      // fall through.
    }
  }

  return up.update_function(time_elpased, up.duration, up.change_value);
}

void Parameterized_Motion::update_logic(const Update_Details &ud)
{
  auto X = Xi::update(upx, get_time_elpased()),
       Y = Xi::update(upy, get_time_elpased());

  position = { X.x, Y.x };
  velocity = { X.y, Y.y };
}

} // namespace Xi

