#ifndef PAINTER_H_INCLUDED_OOQBESXK
#define PAINTER_H_INCLUDED_OOQBESXK

#include "config.h"
#include <SDL2/SDL.h>

namespace Xi {

struct Painter : cc::Disable_Copy, cc::Disable_Move
{
  ::SDL_Renderer         *renderer;

  inline
  void clear_screen(::Uint32 r, ::Uint32 g, ::Uint32 b, ::Uint32 a) const
  {
    ::SDL_SetRenderDrawColor(renderer, r, g, b, a);
    ::SDL_RenderClear(renderer);
  }

  inline
  void draw_rect(::SDL_Rect box, ::Uint32 r, ::Uint32 g, ::Uint32 b, ::Uint32 a) const
  {
    ::SDL_SetRenderDrawColor(renderer, r, g, b, a);
    ::SDL_RenderDrawRect(renderer, &box);
  }

  inline
  void do_render() const
  {
    ::SDL_RenderPresent(renderer);
  }

  inline
  void render_texture(::SDL_Texture *texture,
                      ::SDL_Rect     at) const
  {
    ::SDL_RenderCopy(renderer, texture, nullptr, &at);
  }

  inline
  void render_texture(::SDL_Texture *texture,
                      ::SDL_Rect     at,
                      float_t        angle) const
  {
    ::SDL_RenderCopyEx(renderer,
                       texture,
                       nullptr,
                       &at,
                       angle,
                       nullptr,
                       ::SDL_FLIP_NONE);
  }

  int render_text(const Str &text, int x, int y) const;
};

attr_export const Painter &the_painter();

} // namespace Xi

#endif // end of include guard: PAINTER_H_INCLUDED_OOQBESXK

