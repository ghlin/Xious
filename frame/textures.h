#ifndef TEXTURES_H_INCLUDED_O1DTHFSK
#define TEXTURES_H_INCLUDED_O1DTHFSK

#include "config.h"
#include <SDL2/SDL.h>

namespace Xi {

enum Resource : size_t
{
  TID_Round_Bullet_16x16,
  TID_Round_Bullet_32x32,
  TID_Round_Bullet_64x64,

  TID_Array_Bullet_16x16,
  TID_Array_Bullet_32x32,
  TID_Array_Bullet_64x64,

  TID_Star_Bullet_16x16,
  TID_Star_Bullet_32x32,
  TID_Star_Bullet_64x64,

  TID_Triangle_Bullet_16x16,
  TID_Triangle_Bullet_32x32,
  TID_Triangle_Bullet_64x64,

  TID_Bullet_Bullet_16x16,
  TID_Bullet_Bullet_32x32,
  TID_Bullet_Bullet_64x64,

  TID_Enemy_Ship_16x16,
  TID_Enemy_Ship_32x32,
  TID_Enemy_Ship_64x64,

  TID_Player_Ship_16x16,
  TID_Player_Ship_32x32,
  TID_Player_Ship_64x64,

  SIZE,
};

struct Texture
{
  ::SDL_Texture     *texture;
  int32_t            width,
                     height;
};

attr_export Texture *get_texture(size_t idx);

} // namespace Xi


#endif // end of include guard: TEXTURES_H_INCLUDED_O1DTHFSK

