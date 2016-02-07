#include "movement.h"
#include "../support/animationcurve.h"


// @@@ compile: -E
// @@@ output: /tmp/mm.i

namespace Xi {

XIC_COMPLETE(Movement, f, change_value, duration, limit_value)
XIC_COMPLETE(Movement, u, curve_type, finish_policy)

bool Movement::finished() const
{
  return get_time_elpased() >= get_duration();
}

Phy_Status Movement::do_update(const Update_Details &ud)
{
  if (get_time_elpased() >= get_duration())
  {
    switch (get_finish_policy())
    {
    case U_Stop:
      return { { get_change_value(), 0 }, { } };
    case U_Reset:
      return { };
    }
  }

  switch (get_curve_type())
  {
#define FWD(C) \
  case XI_JOIN(U_, C): \
    { \
      auto v = curve::C::update(get_time_elpased(), get_duration(), get_change_value()); \
      return { { v.x, 0.f }, { v.y, 0.f } }; \
    }

    FWD(Linear);
    FWD(Quadratic);
    FWD(Cubic);
    FWD(Quartic);
    FWD(Quintic);
    FWD(Sinusoidal);
    FWD(Exponential);
  default:
    return { };
  }
}

} // namespace Xi

