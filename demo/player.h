#ifndef PLAYER_H_INCLUDED_G3SHEBDF
#define PLAYER_H_INCLUDED_G3SHEBDF

#include "demo.h"

namespace Xi {

class Player : public Entity
{
public:
  vec_t input = { };

  Player();
};

} // namespace Xi

#endif // end of include guard: PLAYER_H_INCLUDED_G3SHEBDF

