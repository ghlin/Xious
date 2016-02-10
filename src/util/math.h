#ifndef MATH_H_INCLUDED_QF7EQLHW
#define MATH_H_INCLUDED_QF7EQLHW

#include "../config.h"

namespace Xi {

namespace math {

/*
 * A: (a, b), B: (c, d)
 * A x B =>
 *
 * | a   c |
 * |       | = ad - cb
 * | b   d |
 */
static inline
float_t cross_product(const vec_t &A, const vec_t &B)
{
  return A.x * B.y - A.y * B.x;
}


static inline
float_t dot_product(const vec_t &A, const vec_t &B)
{
  return A.x * B.x + A.y * B.y;
}

static inline
bool is_intersect(const vec_t &A1, const vec_t &A2,
                  const vec_t &B1, const vec_t &B2)
{
  auto L1 = B1 - A1, L2 = B1 - A2,
       L3 = B2 - A1, L4 = B2 - A2;

  if ( cross_product(L1, L2) * cross_product(L3, L4) < 0
    && cross_product(L1, L3) * cross_product(L2, L4) < 0)
  {
    return true;
  }

  return false;
}

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


static inline
float side(const vec_t &point,
           const vec_t &A1, const vec_t &A2)
{
  return cross_product(point - A1, point - A2);
}


} // namespace math

} // namespace Xi

#endif // end of include guard: MATH_H_INCLUDED_QF7EQLHW

