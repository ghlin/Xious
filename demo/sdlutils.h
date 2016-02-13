#ifndef SDLUTILS_H_INCLUDED_4QRDWJBG
#define SDLUTILS_H_INCLUDED_4QRDWJBG

#include "demo.h"

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


namespace Xi {

struct SDL_Scope
{
  ::SDL_Window    *window;
  ::SDL_Renderer  *renderer;

  SDL_Scope();
  ~SDL_Scope();

  SDL_Scope(const SDL_Scope &) = delete;
  SDL_Scope(SDL_Scope &&) = delete;
};


} // namespace Xi

#endif // end of include guard: SDLUTILS_H_INCLUDED_4QRDWJBG

