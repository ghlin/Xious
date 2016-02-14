#ifndef FRAMEDEFS_H_INCLUDED_VXJH4P9E
#define FRAMEDEFS_H_INCLUDED_VXJH4P9E

#include "config.h"
#include <SDL2/SDL.h>

namespace Xi {

constexpr const static ::Uint32 FRAME_W = 1000;
constexpr const static ::Uint32 FRAME_H = 620;

constexpr const static ::Uint32 BORDER_X = 10;
constexpr const static ::Uint32 BORDER_Y = 10;

constexpr const static ::Uint32 SCENE_X = BORDER_X;
constexpr const static ::Uint32 SCENE_Y = BORDER_Y;

constexpr const static ::Uint32 SCENE_W = 600;
constexpr const static ::Uint32 SCENE_H = 600;

constexpr const static ::SDL_Rect SCENE_BOX =
{
  SCENE_X, SCENE_Y, SCENE_W, SCENE_H
};

constexpr static const char WINDOW_TITLE[] = "Xious :: Debug Frame";

} // namespace Xi

#endif // end of include guard: FRAMEDEFS_H_INCLUDED_VXJH4P9E

