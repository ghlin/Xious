#ifndef SDLHELPER_H_INCLUDED_DH5PE1FI
#define SDLHELPER_H_INCLUDED_DH5PE1FI

#include "config.h"
#include <SDL2/SDL.h>

namespace Xi {

// {{{ cleanup util
namespace details {

static inline
void free_sdl_pointer(::SDL_Window *window)
{
  if (!window)
  {
    Xi_log("Warning: window is null.");

    return;
  }

  ::SDL_DestroyWindow(window);
}

static inline
void free_sdl_pointer(::SDL_Renderer *renderer)
{
  if (!renderer)
  {
    Xi_log("Warning: renderer is null.");

    return;
  }

  ::SDL_DestroyRenderer(renderer);
}

static inline
void free_sdl_pointer(::SDL_Surface *surface)
{
  if (!surface)
  {
    Xi_log("Warning: surface is null.");

    return;
  }

  ::SDL_FreeSurface(surface);
}

static inline
void free_sdl_pointer(::SDL_Texture *texture)
{
  if (!texture)
  {
    Xi_log("Warning: texture is null.");

    return;
  }

  ::SDL_DestroyTexture(texture);
}


template <typename SDL_Stuff>
static inline
void free_sdl_pointers(SDL_Stuff *ptr)
{
  free_sdl_pointer(ptr);
}

template < typename    SDL_Stuff
         , typename ...SDL_Others>
static inline
void free_sdl_pointers(SDL_Stuff       *ptr,
                       const SDL_Others &...others)
{
  free_sdl_pointer(ptr);
  free_sdl_pointers(others...);
}

} // namespace details
// }}}

template <class ...SDL_Stuff>
static inline
void cleanup_sdl_resource(SDL_Stuff &&...stuff)
{
  details::free_sdl_pointers(stuff...);
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

#endif // end of include guard: SDLHELPER_H_INCLUDED_DH5PE1FI

