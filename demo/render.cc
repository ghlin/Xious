#include "render.h"

namespace Xi {

void SDL_Render::draw(const Draw_Details &dd)
{
  auto *renderer = static_cast<::SDL_Renderer *>(dd.renderer);
  auto *entity = dd.focus;

  ::SDL_Rect target = { 0, 0, 10, 10 };
  // x <- (-ws, ws)
  // y <- (-hs, hs)

  auto pos = entity->get_position();

  target.x = (pos.x + dd.border.ws) * dd.scene_w / (2 * dd.border.ws) - target.w / 2 + G_SCENE_X;
  target.y = (dd.border.hs - pos.y) * dd.scene_h / (2 * dd.border.hs) - target.h / 2 + G_SCENE_Y;

//  Xi_log("draw at (%d, %d) :: (%f, %f).",
//         target.x, target.y,
//         pos.x, pos.y);

  ::SDL_RenderCopyEx(renderer,
                     texture,
                     /* todo */ nullptr,
                     /* todo */ &target,
                     /* todo */ /* :angle: */ 0,
                     /* todo */ /* :center: / SDL_Point */ nullptr,
                     /* todo */ ::SDL_FLIP_NONE);

//  ::SDL_SetRenderDrawColor(renderer, 200, 0, 0, 0);
//  ::SDL_RenderDrawRect(renderer, &target);
}

void SDL_Render::update_logic(const Update_Details &ud)
{ }

} // namespace Xi

