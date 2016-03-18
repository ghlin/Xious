#ifndef MATH_H_INCLUDED_QF7EQLHW
#define MATH_H_INCLUDED_QF7EQLHW

#include "../config.h"

namespace Xi {

namespace math {

constexpr static float_t epsilon = 0.000001f;

static inline
bool eq(float_t lhs, float_t rhs)
{
  return std::abs(lhs - rhs) < epsilon;
}

static inline
bool eq(const vec_t &lhs, const vec_t &rhs)
{
  return eq(lhs.x, rhs.x) && eq(lhs.y, rhs.y);
}

static inline
bool is_zero(float_t v)
{
  return eq(v, 0);
}

static inline
bool is_zero(const vec_t &v)
{
  return eq(v, { 0.0f, 0.0f });
}

static inline
bool is_parallel(const vec_t &a, const vec_t &b)
{
  return eq(a.normalize(), b.normalize());
}

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
vec_t intersection_point(vec_t lpoint, vec_t lnormal,
                         vec_t rpoint, vec_t rnormal)
{
  if (math::is_parallel(lnormal, rnormal))
    return { };

  auto C1 = math::cross_product(lnormal, lpoint),
       C2 = math::cross_product(rnormal, rpoint),
       D  = math::cross_product(rnormal, lnormal),
       x  = math::cross_product({ lnormal.x, rnormal.x }, { C1, C2 }) / D,
       y  = math::cross_product({ lnormal.y, rnormal.y }, { C1, C2 }) / D;

  return { x, y };
}

static inline
bool same_dir_approx(const vec_t &A, const vec_t &B)
{
  return dot_product(A, B) > 0;
}

static inline
bool diff_dir_approx(const vec_t &A, const vec_t &B)
{
  return dot_product(A, B) < 0;
}

static inline
bool same_dir_approx_i(const vec_t &A, const vec_t &B)
{
  return dot_product(A, B) >= 0;
}

static inline
bool diff_dir_approx_i(const vec_t &A, const vec_t &B)
{
  return dot_product(A, B) <= 0;
}

static inline
bool same_sign(float_t a, float_t b)
{
  return (a > 0 && b > 0) || (a < 0 && b < 0);
}

static inline
bool diff_sign(float_t a, float_t b)
{
  return !same_sign(a, b);
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
float_t length_sq(const vec_t &v)
{
  return v.x * v.x + v.y * v.y;
}

static inline
bool is_inside(const vec_t &point,
               const vec_t &centre,
               float_t      radius)
{
  return distance(point, centre) <= radius;
}

static inline
bool is_inside(const vec_t &point,
               const vec_t &centre,
               const vec_t &border)
{
  if ( point.x > centre.x + border.x
    || point.x < centre.x - border.x
    || point.y > centre.y + border.y
    || point.y < centre.y - border.y)
  {
    return false;
  }

  return true;
}

static inline
bool is_inside(const vec_t &P,
               const vec_t &A, const vec_t &B, const vec_t &C)
{
  auto PA = A - P, PB = B - P, PC = C - P;
  auto AB = B - A, AC = C - A;

  auto sum = std::abs(cross_product(PA, PB))
    +        std::abs(cross_product(PC, PB))
    +        std::abs(cross_product(PA, PC));

  auto tri = std::abs(cross_product(AB, AC));

  if (sum > tri)
    return false;

  return true;
}

static inline
float_t side(const vec_t &lpoint,
             const vec_t &rpoint, const vec_t &rdirection)
{
  return cross_product(lpoint - rpoint, lpoint - rpoint - rdirection);
}

static inline
float_t angle(const vec_t &v)
{
  if (is_zero(v))
    return 0;

  return std::atan(v.y / v.x) + (v.x > 0 ? 0 : M_PI);
}

static inline
float_t angle(const vec_t &v, float_t alt)
{
  if (is_zero(v))
    return alt;

  return std::atan(v.y / v.x) + (v.x > 0 ? 0 : M_PI);
}

} // namespace math

} // namespace Xi

#endif // end of include guard: MATH_H_INCLUDED_QF7EQLHW

