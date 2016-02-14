#include "config.h"
#include "../src/support/bootstrap.h"
#include "SDLhelper.h"
#include "painter.h"
#include "framedefs.h"
#include <SDL2/SDL_ttf.h>

namespace Xi {

static Painter      *g_painter = nullptr;
static ::SDL_Window *g_window  = nullptr;

const Painter &the_painter()
{
  return *g_painter;
}

XI_BOOTSTRAP_ON("SDL", { })
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    log_sdlerror("SDL_Init", "");

    Xi_die("sdl error");
  }

  if (TTF_Init() != 0)
  {
    log_sdlerror("TTF_Init", "");

    Xi_die("sdl error");
  }

  auto *window = check_sdl_call(
    ::SDL_CreateWindow(
      WINDOW_TITLE,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      FRAME_W,
      FRAME_H,
      SDL_WINDOW_SHOWN & ~SDL_WINDOW_RESIZABLE));

  auto *renderer = check_sdl_call(
    SDL_CreateRenderer(window,
                       -1,
                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  // load_textures(renderer);

  g_window = window;
  g_painter = new Painter;

  g_painter->renderer = renderer;

  Xi_log("SDL is ready.");
}

XI_BOOTSTRAP_CLEANUP("SDL", { })
{
  cleanup_sdl_resource(g_painter->renderer, g_window);

  Xi_log("SDL cleanup done.");
}

} // namespace Xi

