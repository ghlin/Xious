#include "../../src/actors/movement.h"
#include "../../src/support/animationcurve.h"


int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;

  using namespace Xi;

  Update_Details ud;

  Movement mm;

  auto duration     = 5.f;
  auto change_value = 10000.f;
  using Curve_Type  = curve::Quintic;

  mm.set_duration(duration);
  mm.set_finish_policy(mm.U_Stop);
  mm.set_change_value(change_value);
  mm.set_curve_type(mm.U_Quintic);

  ud.tick_id            = 0;
  ud.delta_time_elpased = 1 / 60.f;
  ud.delta_frame        = 1;

  for (float_t time = 0; time <= 6; time += ud.delta_time_elpased)
  {
    ud.tick_id++;

    auto phy = mm.update(ud);

    Xi_log("%6f : { (%6f, %6f), (%6f, %6f) }",
           time,
           phy.position.x,
           phy.position.y,
           phy.velocity.x,
           phy.velocity.y);
  }

  return 0;
}

