#include "common.h"

// @@@ compile: -E
//
namespace Xi {

XI_DEF_CHAPTER(Simple_Bullet)
  float_t interv = 0;
  float_t dir    = 0;

XI_CHAPTER_INIT()
{
  Xi_log("init chapter %s", Chapter_Title);
}

XI_CHAPTER_UPDATE(ud)
{
  interv += ud.delta_time_elpased;

  if (interv >= 0.1f)
  {
    dir += 0.1;
    game_loop->group->push_back(spawn(nullptr, dir + 0 * M_PI / 3, curve::CT_Linear, 1.0f, 500.0f));
    game_loop->group->push_back(spawn(nullptr, dir + 2 * M_PI / 3, curve::CT_Linear, 1.0f, 500.0f));
    game_loop->group->push_back(spawn(nullptr, dir + 4 * M_PI / 3, curve::CT_Linear, 1.0f, 500.0f));
    interv = 0;
  }
}

} // namespace Xi

