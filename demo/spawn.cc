#include "spawn.h"
#include "bullet.h"
#include "render.h"
#include "roundcollider.h"
#include "textures.h"
#include "updategroup.h"

namespace Xi {

Handle<Entity> spawn(::SDL_Texture    *texture,
                     float_t           dir,
                     curve::Curve_Type curve_type,
                     float_t           duration,
                     float_t           change_value)
{
  auto *entity = new Bullet();
  auto *render = new SDL_Render(texture ?: g_textures[TID_Round_Blue_Bullet]);
  auto *upf    = curve::get_curve(curve_type, curve::CCT_Ease_In);

  auto upx = Update_Parameter
  {
    AP_Continue, upf, duration, change_value * std::cos(dir)
  };

  auto upy = Update_Parameter
  {
    AP_Continue, upf, duration, change_value * std::sin(dir)
  };

  auto *task     = new Parameterized_Movement(upx, upy);
  auto *collider = new Round_Collider;

  entity->render   = Handle<Render>(render);
  entity->task     = Handle<Task>(task);
  entity->collider = Handle<Collider>(collider);
  entity->flags    = Die_If_Move_Off_Screen;
  entity->state    = ES_Normal;

  return Handle<Entity>(entity);
}

} // namespace Xi

