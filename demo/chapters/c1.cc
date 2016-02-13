#include "common.h"

namespace Xi {

XI_DEF_CHAPTER(Simple_Bullet_2)
  float_t shoot_timer    = 0;
  float_t stop_timer     = 0;
  float_t dir_timer      = 0;
  float_t si_timer       = 0;

  float_t dir            = 0.0f;

  float_t shoot_interv   = 0.02f;
  float_t stop_duration  = 0.5f;
  float_t shoot_duration = 0.5f;

  int     state          = 1;
  int     cct            = 0;

XI_CHAPTER_INIT()
{
  Xi_log("init chapter %s", Chapter_Title);
}

XI_CHAPTER_UPDATE(ud)
{
  if (state == 0)
  {
    if ((stop_timer += ud.delta_time_elpased) > stop_duration)
    {
      stop_timer = 0;
      state = 1;
      cct = (cct + 1) % 3;
    }
  }
  else if (state == 1)
  {
    if ((shoot_timer += ud.delta_time_elpased) > shoot_duration)
    {
      state = 0;
      shoot_timer = 0;
    }

    if ((si_timer += ud.delta_time_elpased) > shoot_interv)
    {
      si_timer = 0;

      constexpr curve::Curve_Change_Type ccts[] =
      {
        curve::CCT_Ease_In,
        curve::CCT_Ease_Out,
        curve::CCT_Ease_In_Out
      };

      constexpr int N = 6;
      for (int i = 0; i != N; ++i)
      {
        for (int k = 0; k != 3; ++k)
        {
          game_loop->group->push_back(spawn(
              nullptr,
              get_time_elpased() + i * 2 * M_PI / N + k * 0.1f,
              curve::CT_Quintic,
              curve::CCT_Ease_In_Out,
              1.0f,
              300.0f + k * 50));
        }
      }

    }
  }


}

} // namespace Xi


