#include "textures.h"
#include "painter.h"
#include "SDLhelper.h"

#include "../src/support/bootstrap.h"

#include <SDL2/SDL_image.h>
#include <cctype>

namespace Xi {

constexpr size_t Chars = CHAR_MAX;

struct RC_Pack
{
  Texture rc[Resource::SIZE + Chars] = { };
};

static RC_Pack *_rc_pack()
{
  static RC_Pack _;
  return &_;
}


static inline
Texture load_texture(::SDL_Renderer *renderer, const Str &filename)
{
  auto *texture = check_sdl_call(::IMG_LoadTexture(renderer, filename.c_str()));

  if (!texture)
  {
    Xi_die("Failed loaded texture [" + filename + "].");

    return { nullptr, 0, 0 };
  }

  int w, h;
  ::SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

  Xi_log("Texture %s loaded => (%d x %d).", filename, w, h);

  return { texture, w, h };
}

XI_BOOTSTRAP_ON("textures", { "SDL" })
{
  ::SDL_Renderer *renderer = the_painter().renderer;

  for (size_t i = 0; i != 32; ++i)
    _rc_pack()->rc[i] = load_texture(renderer, "../rc/"s + u_stringify(i) + ".png");
}

} // namespace Xi

