#ifndef COLLISION_H_INCLUDED_NTH4ZFPL
#define COLLISION_H_INCLUDED_NTH4ZFPL

#include "config.h"

namespace Xi {

using Collision_Grid = std::vector<Entity *>;

struct Collision_Grid_Group
{
  std::vector<
    std::vector<
      Collision_Grid>> grids;
};

} // namespace Xi

#endif // end of include guard: COLLISION_H_INCLUDED_NTH4ZFPL

