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
  XI_UNUSED(A1, A2, B1, B2);

  // TODO(ghlin) : 2016-02-10 20:38:34
  return false;
}

} // namespace math

} // namespace Xi

#endif // end of include guard: MATH_H_INCLUDED_QF7EQLHW

