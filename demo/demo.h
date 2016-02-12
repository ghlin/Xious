#ifndef DEMO_H_INCLUDED_PGBTE3S4
#define DEMO_H_INCLUDED_PGBTE3S4

#include "../src/all.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace Xi {

static inline
void free_sdl_pointer(SDL_Window *window)
{
  if (!window)
    return;

  SDL_DestroyWindow(window);
}

static inline
void free_sdl_pointer(SDL_Renderer *renderer)
{
  if (!renderer)
    return;

  SDL_DestroyRenderer(renderer);
}

static inline
void free_sdl_pointer(SDL_Surface *surface)
{
  if (!surface)
    return;

  SDL_FreeSurface(surface);
}

static inline
void free_sdl_pointer(SDL_Texture *texture)
{
  if (!texture)
    return;

  SDL_DestroyTexture(texture);
}


template <typename SDL_Something>
static inline
void free_sdl_pointers(SDL_Something *ptr)
{
  free_sdl_pointer(ptr);
}

template < typename    SDL_Something
         , typename ...SDL_Others>
static inline
void free_sdl_pointers(SDL_Something       *ptr,
                       const SDL_Others &...others)
{
  free_sdl_pointer(ptr);
  free_sdl_pointers(others...);
}

} // namespace Xi

#define log_sdlerror(sdlcall, _extrafmt, ...)        \
  do {                                               \
    Str extrafmt = _extrafmt;                        \
    Xi_log("%s raised an error: %s%s"                \
            + extrafmt, extrafmt.empty() ? "" : " ", \
            sdlcall, SDL_GetError(), ##__VA_ARGS__); \
  } while (false)

#define check_sdl_call(call_expr)                  \
  ({                                               \
    auto *result = (call_expr);                    \
    if (!result)                                   \
    {                                              \
      log_sdlerror(XI_STRINGIFY(call_expr), "");   \
    }                                              \
                                                   \
    /* return */ result;                           \
 })
#define check_and_cleanup_later(ptr) \
  Xi_runtime_check(ptr != nullptr); \
  auto XI_JOIN(__cleanup_dummy_, __COUNTER__) = u_defer_with (ptr) { free_sdl_pointer(ptr); }


#define G_SCENE_X  10
#define G_SCENE_Y  10
#define G_SCENE_W  600
#define G_SCENE_H  600
#define G_WINDOW_W 900
#define G_WINDOW_H 700
#define G_WORLD_W  1200.0f
#define G_WORLD_H  1200.0f

namespace Xi {

class Game_Loop;
class Update_Group;

} // namespace Xi

#endif // end of include guard: DEMO_H_INCLUDED_PGBTE3S4

