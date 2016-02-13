#include "common.h"

namespace Xi {

XI_DEF_CHAPTER(Simple_Bullet)

XI_CHAPTER_INIT()
{
  Xi_log("init chapter %s", Chapter_Title);
}

XI_CHAPTER_UPDATE(ud)
{
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
          curve::CCT_Ease_Out,
          1.0f,
          300.0f + k * 50));
    }
  }
}

} // namespace Xi



