#include "textures.h"

namespace Xi {


::SDL_Texture *g_textures[kMax_Textrues] = { };

::SDL_Texture *load_texture(::SDL_Renderer *renderer, const Str &path)
{
  auto *texture = check_sdl_call(::IMG_LoadTexture(renderer, path.c_str()));

  Xi_log("loaded %s.", path);

  return texture;
}


void load_textures(::SDL_Renderer *renderer)
{
  auto texture_prefix = "/Users/ghlin/Workspace/Xious/test/textrues/"s;

  g_textures[TID_Round_Blue_Bullet] = load_texture(renderer, texture_prefix + "DpBlueBulletC.png");
}

} // namespace Xi
