#ifndef COLLISTATUS_H_INCLUDED_0TP4TDRC
#define COLLISTATUS_H_INCLUDED_0TP4TDRC

#include "../config.h"
#include "../util/math.h"

namespace Xi {

enum Collision_Model_Type
{
  CM_Box,
  CM_Round,
  CM_Segment,
  CM_Straight_Line,
};

struct Box_Model
{
  vec_t        border;
};

struct Round_Model
{
  float_t      radius;
};

struct Segment_Model
{
  vec_t         ending;
};

struct Straight_Line_Model
{
  vec_t         normal;
};

// Round_Model x Round_Model
// Round_Model x Box_Model
// Round_Model x Segment_Model
// Round_Model x Straight_Line_Model
// Box_Model x Box_Model
// Box_Model x Segment_Model
//*Box_Model x Straight_Line_Model
// Segment_Model x Segment_Model
//*Segment_Model x Straight_Line_Model
//*Straight_Line_Model x Straight_Line_Model

namespace details {
static inline
bool is_inside(const vec_t &point,
               const vec_t &centre,
               float_t      radius)
{
  return glm::distance(point, centre) < radius;
}

static inline
bool is_inside(const vec_t &point,
               const vec_t &centre,
               const vec_t &border)
{
  if ( point.x > centre.x - border.x
    || point.x < centre.x + border.x
    || point.y > centre.y - border.y
    || point.y < centre.y + border.y)
  {
    return false;
  }

  return true;
}

} // namespace details

/**
 * Round_Model x Round_Model.
 */
static inline
bool is_colliding(const Round_Model   &A,
                  const vec_t         &pos_A,
                  const Round_Model   &B,
                  const vec_t         &pos_B)
{
  return glm::distance(pos_A, pos_B) < A.radius + B.radius;
}


/**
 * Round_Model x Straight_Line_Model
 */
bool is_colliding(const Round_Model         &A,
                  const vec_t               &pos_A,
                  const Straight_Line_Model &B,
                  const vec_t               &pos_B)
{
  auto L1     = pos_A - pos_B,
       L2     = L1    - B.normal;
  auto length = glm::distance(pos_B, B.normal);

  return math::cross_product(L1, L2) < length * A.radius;
}

/**
 * Round_Model x Segment_Model
 */
static inline
bool is_colliding(const Round_Model     &A,
                  const vec_t           &pos_A,
                  const Segment_Model   &B,
                  const vec_t           &pos_B)
{
  if (details::is_inside(pos_B, pos_A, A.radius)
    || details::is_inside(B.ending + pos_B, pos_A, A.radius))
  {
    return true;
  }

  return is_colliding(A, pos_A, Straight_Line_Model { B.ending }, pos_B);
}

/**
 * Round_Model x Box_Model
 */
static inline
bool is_colliding(const Round_Model  &A,
                  const vec_t        &pos_A,
                  const Box_Model    &B,
                  const vec_t        &pos_B)
{
  if ( pos_A.x - A.radius > pos_B.x + B.border.x
    || pos_A.x + A.radius < pos_B.x - B.border.x
    || pos_A.y - A.radius > pos_B.y + B.border.y
    || pos_A.y + A.radius < pos_B.y - B.border.y)
  {
    return false;
  }

  if (details::is_inside(pos_B, pos_A, A.radius))
    return true;

  auto care = glm::normalize(pos_B - pos_A) * A.radius + pos_A;

  return details::is_inside(care, pos_B, B.border);
}



/**
 * Box_Model x Box_Model
 */
static inline
bool is_colliding(const Box_Model &A,
                  const vec_t      &pos_A,
                  const Box_Model &B,
                  const vec_t      &pos_B)
{
  if ( pos_A.x + A.border.x < pos_B.x - B.border.x
    || pos_A.x - A.border.x > pos_B.x + B.border.x
    || pos_A.y + A.border.y < pos_B.y - B.border.y
    || pos_A.y - A.border.y > pos_B.y + B.border.y)
  {
    return false;
  }

  return true;
}

/**
 * Segment_Model x Segment_Model
 */
static inline
bool is_colliding(const Segment_Model &A,
                  const vec_t         &pos_A,
                  const Segment_Model &B,
                  const vec_t         &pos_B)
{
  return math::is_intersect(pos_A + A.ending, pos_A, pos_B + B.ending, pos_B);
}

/**
 * Box_Model x Segment_Model
 */
static inline
bool is_colliding(const Box_Model          &A,
                  const vec_t              &pos_A,
                  const Segment_Model      &B,
                  const vec_t              &pos_B)
{
  if ( details::is_inside(pos_B, pos_A, A.border)
    || details::is_inside(pos_B + B.ending, pos_A, A.border))
  {
    return true;
  }

  vec_t LU = { pos_A.x - A.border.x, pos_A.y + A.border.y },
        LB = { pos_A.x - A.border.x, pos_A.y - A.border.y },
        RU = { pos_A.x + A.border.x, pos_A.y + A.border.y },
        RB = { pos_A.x + A.border.x, pos_A.y - A.border.y };

  return math::is_intersect(LU, LB, pos_B, pos_B + B.ending)
    ||   math::is_intersect(RU, RB, pos_B, pos_B + B.ending)
    ||   math::is_intersect(RU, RU, pos_B, pos_B + B.ending)
    ||   math::is_intersect(RB, RB, pos_B, pos_B + B.ending);
}

} // namespace Xi

#endif // end of include guard: COLLISTATUS_H_INCLUDED_0TP4TDRC

