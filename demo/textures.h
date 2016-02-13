#ifndef TEXTURES_H_INCLUDED_FZEPHIKB
#define TEXTURES_H_INCLUDED_FZEPHIKB

#include "demo.h"

namespace Xi {

constexpr size_t kMax_Textrues = 32;
constexpr size_t TID_Round_Blue_Bullet = 0;
constexpr size_t TID_Round_Green_Bullet = 1;

extern ::SDL_Texture *g_textures[kMax_Textrues];

void load_textures(::SDL_Renderer *renderer);

int render_text(::SDL_Renderer *renderer,
                 int x, int y,
                 const Str &text);

void free_textures();

} // namespace Xi


#endif // end of include guard: TEXTURES_H_INCLUDED_FZEPHIKB

