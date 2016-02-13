#include "sdlutils.h"
#include "textures.h"


namespace Xi {

SDL_Scope::SDL_Scope()
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

  window = check_sdl_call(
    ::SDL_CreateWindow(
      "STG Demo :: Demo",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      G_WINDOW_W,
      G_WINDOW_H,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));

  renderer = check_sdl_call(
    SDL_CreateRenderer(window,
                       -1,
                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  load_textures(renderer);

  Xi_log("init done.");
}

SDL_Scope::~SDL_Scope()
{
  free_sdl_pointers(renderer, window);
  free_textures();

  SDL_Quit();

  Xi_log("Bye.");
}


} // namespace Xi

