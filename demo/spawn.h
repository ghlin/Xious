#ifndef SPAWN_H_INCLUDED_M8S7YZA3
#define SPAWN_H_INCLUDED_M8S7YZA3

#include "demo.h"

namespace Xi {

attr_export
Handle<Entity> spawn(::SDL_Texture           *texture,
                     float_t                  dir,
                     curve::Curve_Type        curve_type,
                     curve::Curve_Change_Type cct,
                     float_t                  duration,
                     float_t                  change_value);
} // namespace Xi

#endif // end of include guard: SPAWN_H_INCLUDED_M8S7YZA3

