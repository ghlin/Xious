#include "textures.h"
#include "sdlutils.h"


namespace Xi {


::SDL_Texture *g_textures[kMax_Textrues]                         = { };
::SDL_Texture *g_text_textures[std::numeric_limits<char>::max()] = { };
::SDL_Rect     g_text_textures_rect[std::numeric_limits<char>::max()] = { };

void free_textures()
{
  for (auto &p : g_textures)
    free_sdl_pointer(p);
  for (auto &p : g_text_textures)
    free_sdl_pointer(p);
}

::SDL_Texture *load_texture(::SDL_Renderer *renderer, const Str &path)
{
  auto *texture = check_sdl_call(::IMG_LoadTexture(renderer, path.c_str()));

  return texture;
}

::SDL_Texture *load_text_texture(::SDL_Renderer *renderer,
                                 ::TTF_Font       *font,
                                 char              ch)
{
  char pch[2] = { ch, '\0' };

  ::SDL_Surface *surface = check_sdl_call(TTF_RenderText_Solid(font, pch, { 255, 255, 255 }));
  ::SDL_Texture *texture = check_sdl_call(SDL_CreateTextureFromSurface(renderer, surface));

  SDL_FreeSurface(surface);

  return texture;
}


void load_textures(::SDL_Renderer *renderer)
{
  auto texture_prefix = "/Users/ghlin/Workspace/Xious/test/textrues/"s;

  g_textures[TID_Round_Blue_Bullet]  = load_texture(renderer, texture_prefix + "DpBlueBulletC.png");
  g_textures[TID_Round_Green_Bullet] = load_texture(renderer, texture_prefix + "PsBulletC.png");

  auto font_path = texture_prefix + "OpenSans-Regular.ttf";

  ::TTF_Font *font = TTF_OpenFont(font_path.c_str(), 16);

  for (int ch = 0; ch != std::numeric_limits<char>::max(); ++ch)
  {
    if (std::isprint(ch))
      g_text_textures[ch] = load_text_texture(renderer, font, ch);
    else
      g_text_textures[ch] = load_text_texture(renderer, font, '.');

    ::SDL_QueryTexture(g_text_textures[ch], nullptr, nullptr, &g_text_textures_rect[ch].w, &g_text_textures_rect[ch].h);
  }

  TTF_CloseFont(font);
}

int render_text(::SDL_Renderer *renderer,
                 int x, int y,
                 const Str &text)
{
  int pos_x = x, pos_y = y;

  for (auto ch : text)
  {
    ::SDL_Rect  target = { pos_x, pos_y, g_text_textures_rect[ch].w, g_text_textures_rect[ch].h };
    ::SDL_RenderCopy(renderer, g_text_textures[ch], nullptr, &target);

    if ((pos_x += g_text_textures_rect[ch].w) > G_WINDOW_W || ch == '\n')
    {
      pos_x = x;
      pos_y += g_text_textures_rect[ch].h;
    }
  }

  return pos_y;
}

} // namespace Xi
