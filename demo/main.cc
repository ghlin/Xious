#include "demo.h"
#include "textures.h"
#include "gameloop.h"

namespace Xi {


float fps_delta_time(unsigned fps)
{
  return 1.0f / fps;
}

template <class T>
bool fps_ctrl(T *last, unsigned fps)
{

  return true;
}

} // namespace Xi

int main(int argc, const char **argv)
{
  using namespace Xi;

  init::bootstrap_initialize(argc, argv);

  // {{{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    log_sdlerror("SDL_Init", "");

    return -1;
  }

  auto _1 = u_defer { SDL_Quit(); };

  auto *window = check_sdl_call(
    ::SDL_CreateWindow(
      "STG Demo :: Demo",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      G_WINDOW_W,
      G_WINDOW_H,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));

  check_and_cleanup_later(window);

  auto renderer = check_sdl_call(
    SDL_CreateRenderer(window,
                       -1,
                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  check_and_cleanup_later(window);
  // }}}

  load_textures(renderer);

  SDL_Event  e;
  Game_Loop gl(renderer);

  unsigned long long tick             = 0;
  auto               last_update_time = std::chrono::high_resolution_clock::now();
  auto               vary_beginning   = last_update_time;
  auto               CONFIG_FPS       = 60;

  float_t            fps              = 0.0f;

  SDL_Rect g_scene_rect = { G_SCENE_X, G_SCENE_Y, G_SCENE_W, G_SCENE_H };
  SDL_Rect fpsrept_rect = { 0, 0, G_SCENE_X, G_SCENE_Y };

  do
  {
    auto before_update                = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> diff = before_update - last_update_time;

    if (diff.count() < fps_delta_time(CONFIG_FPS))
    {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, 122, 122, 122, 0);
      SDL_RenderDrawRect(renderer, &g_scene_rect);

      gl.render();

      if (fps < 30.0f)
        SDL_SetRenderDrawColor(renderer, 250, 0, 0, 0);
      else if (fps < 50.0f)
        SDL_SetRenderDrawColor(renderer, 0, 250, 0, 0);
      else if (fps > 60.0f)
        SDL_SetRenderDrawColor(renderer, 0, 0, 250, 0);
      else
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);

      SDL_RenderDrawRect(renderer, &fpsrept_rect);
      SDL_RenderPresent(renderer);
    }
    else
    {
      gl.update(diff.count());
      ++tick;

      auto after_update = std::chrono::high_resolution_clock::now();
      std::chrono::duration<float> update_time_elpased = before_update  - after_update;
      std::chrono::duration<float> total_time_elpased  = vary_beginning - after_update;

      fps = tick / total_time_elpased.count();

      last_update_time = after_update;
    }

    while (SDL_PollEvent(&e) && e.type != SDL_QUIT)
      ;
  } while (e.type != SDL_QUIT);

  init::bootstrap_finalize();

  return 0;
}

