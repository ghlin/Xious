#ifndef COLLISTATUS_H_INCLUDED_0TP4TDRC
#define COLLISTATUS_H_INCLUDED_0TP4TDRC

#include "../config.h"
#include "../util/math.h"

namespace Xi {

enum Collision_Model_Type
{
  CM_Special,
  CM_Line,     ///< 直线 (两端延伸)
  CM_Segment,  ///< 线段
  CM_Box,      ///< 长方形 (不考虑旋转)
  CM_Round,    ///< 圆形
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

struct Line_Model
{
  vec_t         normal;
};

struct Collision_Model
{
  Collision_Model_Type type;

  union {
    Round_Model   round;
    Box_Model     box;
    Segment_Model segment;
    Line_Model    line;
  };
};

// Round_Model x Round_Model
// Round_Model x Box_Model
// Round_Model x Segment_Model
// Round_Model x Line_Model
// Box_Model x Box_Model
// Box_Model x Segment_Model
// Box_Model x Line_Model
// Segment_Model x Segment_Model
// Segment_Model x Line_Model
// Line_Model x Line_Model


/**
 * Round_Model x Round_Model.
 */
static inline
bool is_colliding(const vec_t       &pos_A,
                  const Round_Model &A,
                  const vec_t       &pos_B,
                  const Round_Model &B)
{
  return glm::distance(pos_A, pos_B) < A.radius + B.radius;
}


/**
 * Round_Model x Line_Model
 */
static inline
bool is_colliding(const vec_t       &pos_A,
                  const Round_Model &A,
                  const vec_t       &pos_B,
                  const Line_Model  &B)
{
  auto L1     = pos_A - pos_B,
       L2     = L1 - B.normal;

  auto length   = B.normal.length();
  auto distance = std::abs(math::cross_product(L1, L2)) / length;

  return distance < A.radius;
}

/**
 * Round_Model x Segment_Model
 */
static inline
bool is_colliding(const vec_t         &pos_A,
                  const Round_Model   &A,
                  const vec_t         &pos_B,
                  const Segment_Model &B)
{
  auto pass1 = math::is_inside(pos_B, pos_A, A.radius),
       pass2 = math::is_inside(pos_B + B.ending, pos_A, A.radius);

  if (pass1 || pass2)
    return true;

  auto dir = glm::normalize(B.ending);
  vec_t P1 = { pos_A.x + dir.y, pos_A.y - dir.x },
        P2 = { pos_A.x - dir.y, pos_A.y + dir.x };

  return math::is_intersect(pos_B, pos_B + B.ending, P1, P2);
}

/**
 * Round_Model x Box_Model
 */
static inline
bool is_colliding(const vec_t       &pos_A,
                  const Round_Model &A,
                  const vec_t       &pos_B,
                  const Box_Model   &B)
{
  if ( pos_A.x - A.radius > pos_B.x + B.border.x
    || pos_A.x + A.radius < pos_B.x - B.border.x
    || pos_A.y - A.radius > pos_B.y + B.border.y
    || pos_A.y + A.radius < pos_B.y - B.border.y)
  {
    return false;
  }

  if (math::is_inside(pos_B, pos_A, A.radius))
    return true;

  // FIXME(ghlin) : 算法有误 2016-02-14 17:56:56
  //  应该计算 长方形中点与圆中点连线 与 长方形边交点 是否位于圆内

  auto care = glm::normalize(pos_B - pos_A) * A.radius + pos_A;

  return math::is_inside(care, pos_B, B.border);
}



/**
 * Box_Model x Box_Model
 */
static inline
bool is_colliding(const vec_t     &pos_A,
                  const Box_Model &A,
                  const vec_t     &pos_B,
                  const Box_Model &B)
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
bool is_colliding(const vec_t         &pos_A,
                  const Segment_Model &A,
                  const vec_t         &pos_B,
                  const Segment_Model &B)
{
  return math::is_intersect(pos_A + A.ending, pos_A, pos_B + B.ending, pos_B);
}

/**
 * Segment_Model x Line_Model
 */
static inline
bool is_colliding(const vec_t         &pos_A,
                  const Segment_Model &A,
                  const vec_t         &pos_B,
                  const Line_Model    &B)
{
  auto S1 = math::side(pos_A, pos_B, pos_B + B.normal),
       S2 = math::side(pos_A + A.ending, pos_B, pos_B + B.normal);

  return S1 * S2 < 0;
}

/**
 * Box_Model x Segment_Model
 */
static inline
bool is_colliding(const vec_t         &pos_A,
                  const Box_Model     &A,
                  const vec_t         &pos_B,
                  const Segment_Model &B)
{
  if ( math::is_inside(pos_B, pos_A, A.border)
    || math::is_inside(pos_B + B.ending, pos_A, A.border))
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

/**
 * Box_Model x Line_Model
 */
static inline
bool is_colliding(const vec_t      &pos_A,
                  const Box_Model  &A,
                  const vec_t      &pos_B,
                  const Line_Model &B)
{
  vec_t LU = { pos_A.x - A.border.x, pos_A.y + A.border.y },
        RB = { pos_A.x + A.border.x, pos_A.y - A.border.y };

  vec_t H = { 2 * A.border.x, 0 },
        V = { 0, 2 * A.border.y };

  return is_colliding(LU, Segment_Model {  H }, pos_B, B)
    ||   is_colliding(LU, Segment_Model { -V }, pos_B, B)
    ||   is_colliding(RB, Segment_Model { -H }, pos_B, B)
    ||   is_colliding(RB, Segment_Model {  V }, pos_B, B);
}

/**
 * Line_Model x Line_Model
 */
static inline
bool is_colliding(const vec_t      &pos_A,
                  const Line_Model &A,
                  const vec_t      &pos_B,
                  const Line_Model &B)
{
  // FIXME(ghlin) : 处理共线 2016-02-10 23:04:54
  XI_UNUSED(pos_A, pos_B);

  return std::abs(math::cross_product(A.normal, B.normal)) > std::numeric_limits<float_t>::epsilon();
}

} // namespace Xi

#endif // end of include guard: COLLISTATUS_H_INCLUDED_0TP4TDRC

