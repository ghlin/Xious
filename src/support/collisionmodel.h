#ifndef COLLISTATUS_H_INCLUDED_0TP4TDRC
#define COLLISTATUS_H_INCLUDED_0TP4TDRC

#include "../config.h"

namespace Xi {

enum Collision_Model_Type
{
  CM_Bounding_Box,
  CM_Round,
};


//  +--------------------------------+
//  |               ^ vertical       |
//  |               |                |
//  |               |                |
//  |               v                |
//  |            centre <----------->|
//  |                     horizontal |
//  |                                |
//  |                                |
//  |                                |
//  +--------------------------------+
struct Bounding_Box_Model
{
  float_t      horizontal;
  float_t      vertical;
};

struct Round_Model
{
  float_t      radius;
};

struct Collision_Model
{
  Collision_Model_Type type;

  union
  {
    Bounding_Box_Model bounding_box;
    Round_Model        round;
  };
};

static inline
bool is_colliding(const Bounding_Box_Model &A,
                  const vec2               &pos_A,
                  const Bounding_Box_Model &B,
                  const vec2               &pos_B)
{
  if ( pos_A.x + A.horizontal < pos_B.x - B.horizontal
    || pos_A.x - A.horizontal > pos_B.x + B.horizontal
    || pos_A.y + A.vertical   < pos_B.y - B.vertical
    || pos_A.y - A.vertical   > pos_B.y + B.vertical)
    return false;

  return true;
}

static inline
bool is_colliding(const Round_Model &A,
                  const vec2        &pos_A,
                  const Round_Model &B,
                  const vec2        &pos_B)
{
  if (std::abs((pos_A.x - pos_B.x) * (pos_A.y - pos_B.y)) > A.radius + B.radius)
    return false;

  return true;
}

static inline
bool is_colliding(const Round_Model        &A,
                  const vec2               &pos_A,
                  const Bounding_Box_Model &B,
                  const vec2               &pos_B)
{
  // TODO(ghlin) : 2016-02-08 20:36:51

  return is_colliding({ A.radius, A.radius }, pos_A, B, pos_B);
}

} // namespace Xi

#endif // end of include guard: COLLISTATUS_H_INCLUDED_0TP4TDRC

