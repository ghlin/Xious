#include "gameloop.h"
#include "updategroup.h"
#include "render.h"
#include "roundcollider.h"
#include "chapter.h"

namespace Xi {

Game_Loop::Game_Loop(::SDL_Renderer *renderer)
  : dd { }
  , group(new Update_Group)
{
  dd.renderer = static_cast<SDL_Renderer *>(renderer);
  change_chapter(get_chapters().front());

  dd.border.width  = G_WORLD_W;
  dd.border.height = G_WORLD_H;
  dd.border.ws     = G_WORLD_W / 2;
  dd.border.hs     = G_WORLD_H / 2;

  dd.scene_w       = G_SCENE_W;
  dd.scene_h       = G_SCENE_H;

  Xi_log("锵锵锵!!!!");
}

void Game_Loop::update(float_t dt)
{
  dd.delta_time_elpased  = dt;
  dd.time_elpased       += dt;
  dd.frame++;

  dd.focus   = nullptr;

  chapter->update(dd);
  group->update(dd);
}

void Game_Loop::render()
{
  group->draw(dd);
}

} // namespace Xi

