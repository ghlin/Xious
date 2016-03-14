#ifndef COLLISION_H_INCLUDED_I9WTG7HW
#define COLLISION_H_INCLUDED_I9WTG7HW

#include "../config.h"
#include "math.h"

namespace Xi {

enum Collision_Model_Type : uint32_t
{
  CMT_Special,
  CMT_Point,
  CMT_Line,
  CMT_Ray,
  CMT_Segment,
  CMT_Box,
  CMT_Circle,
};

struct Collision_Model_Data
{
  union {
    vec_t centre;
    vec_t begin_point;
    vec_t point;
    vec_t v1;
  };

  union {
    vec_t   direction;
    vec_t   end_point;
    vec_t   border;
    float_t radius;

    vec_t   v2;
    float_t f2;
  };

  Collision_Model_Data(const vec_t v1, const vec_t v2)
    : v1(v1), v2(v2) { }

  Collision_Model_Data(const vec_t v1, float_t f2)
    : v1(v1), f2(f2) { }
};

struct Collision_Model
{
  Collision_Model_Type type;
  Collision_Model_Data data;
};

namespace details {
template <uint32_t E, uint32_t T>
struct Model_Tag
{
  struct prio { enum uint32_t { value = E }; };
  struct take { enum uint32_t { value = T }; };
};

using Point_Model_Tag   = Model_Tag<CMT_Point, 1>;
using Line_Model_Tag    = Model_Tag<CMT_Line, 2>;
using Ray_Model_Tag     = Model_Tag<CMT_Ray, 2>;
using Segment_Model_Tag = Model_Tag<CMT_Segment, 2>;
using Box_Model_Tag     = Model_Tag<CMT_Box, 2>;
using Circle_Model_Tag  = Model_Tag<CMT_Circle, 2>;

} // namespace details

constexpr static details::Point_Model_Tag   point_model_tag   = { };
constexpr static details::Line_Model_Tag    line_model_tag    = { };
constexpr static details::Ray_Model_Tag     ray_model_tag     = { };
constexpr static details::Segment_Model_Tag segment_model_tag = { };
constexpr static details::Box_Model_Tag     box_model_tag     = { };
constexpr static details::Circle_Model_Tag  circle_model_tag  = { };

namespace details {

/**
 * Point x Point
 */
static inline
bool is_colliding(const Point_Model_Tag &,
                  const Point_Model_Tag &,
                  vec_t lpoint,
                  vec_t rpoint)
{
  return math::eq(lpoint, rpoint);
}

/**
 * Point x Line
 */
static inline
bool is_colliding(const Point_Model_Tag &,
                  const Line_Model_Tag  &,
                  vec_t lpoint,
                  vec_t rpoint,
                  vec_t rdirection)
{
  return math::is_zero(math::cross_product(rpoint - lpoint, rdirection));
}

/**
 * Point x Ray
 */
static inline
bool is_colliding(const Point_Model_Tag &,
                  const Ray_Model_Tag   &,
                  vec_t lpoint,
                  vec_t rpoint,
                  vec_t rdirection)
{
  return is_colliding(point_model_tag, line_model_tag, lpoint, rpoint, rdirection)
    &&   math::same_dir_approx_i(lpoint - rpoint, rdirection);
}

/**
 * Point x Segment
 */
static inline
bool is_colliding(const Point_Model_Tag   &,
                  const Segment_Model_Tag &,
                  vec_t lpoint,
                  vec_t rbegin_point,
                  vec_t rend_point)
{
  return is_colliding(point_model_tag, ray_model_tag, lpoint, rbegin_point, rend_point - rbegin_point)
    &&   is_colliding(point_model_tag, ray_model_tag, lpoint, rbegin_point, rbegin_point - rend_point);
}

/**
 * Point x Box
 */
static inline
bool is_colliding(const Point_Model_Tag &,
                  const Box_Model_Tag   &,
                  vec_t lpoint,
                  vec_t rcentre,
                  vec_t rborder)
{
  if ( lpoint.x > rcentre.x + rborder.x
    || lpoint.x < rcentre.x - rborder.x
    || lpoint.y > rcentre.y + rborder.y
    || lpoint.y < rcentre.y - rborder.y)
  {
    return false;
  }

  return true;
}

/**
 * Point x Circle
 */
static inline
bool is_colliding(const   Point_Model_Tag  &,
                  const   Circle_Model_Tag &,
                  vec_t   lpoint,
                  vec_t   rcentre,
                  float_t radius)
{
  return radius * radius >= math::length_sq(rcentre - lpoint);
}

/**
 * Line x Line
 */
static inline
bool is_colliding(const Line_Model_Tag &,
                  const Line_Model_Tag &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rpoint,
                  vec_t rdirection)
{
  return !math::is_parallel(ldirection, rdirection)
    &&   !math::is_parallel(ldirection, lpoint - rpoint);
}

/**
 * Line x Ray
 */
static inline
bool is_colliding(const Line_Model_Tag &,
                  const Ray_Model_Tag  &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rpoint,
                  vec_t rdirection)
{
  if (math::is_parallel(ldirection, rdirection))
    return !math::is_parallel(ldirection, lpoint - rpoint);

  auto cross = math::intersection_point(lpoint, ldirection, rpoint, rdirection);

  return math::same_dir_approx_i(cross - lpoint, ldirection);
}

/**
 * Line x Segment
 */
static inline
bool is_colliding(const Line_Model_Tag    &,
                  const Segment_Model_Tag &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rbegin_point,
                  vec_t rend_point)
{
  if (math::is_parallel(ldirection, rend_point - rbegin_point))
    return !math::is_parallel(ldirection, rbegin_point - lpoint);

  auto cross = math::intersection_point(lpoint, ldirection, rbegin_point, rend_point - rbegin_point);

  return math::same_dir_approx_i(cross - rbegin_point, cross - rend_point);
}

/**
 * Line x Box
 */
static inline
bool is_colliding(const Line_Model_Tag &,
                  const Box_Model_Tag  &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rcentre,
                  vec_t rborder)
{
  vec_t vertices[] =
  { { rcentre.x - rborder.x, rcentre.y + rborder.y }
  , { rcentre.x + rborder.x, rcentre.y + rborder.y }
  , { rcentre.x + rborder.x, rcentre.y - rborder.y }
  , { rcentre.x - rborder.x, rcentre.y - rborder.y } };

  if ( is_colliding(line_model_tag, segment_model_tag, lpoint, ldirection, vertices[0], vertices[1])
    || is_colliding(line_model_tag, segment_model_tag, lpoint, ldirection, vertices[1], vertices[2])
    || is_colliding(line_model_tag, segment_model_tag, lpoint, ldirection, vertices[2], vertices[3])
    || is_colliding(line_model_tag, segment_model_tag, lpoint, ldirection, vertices[3], vertices[0]))
  {
    return true;
  }

  return false;
}

/**
 * Line x Circle
 */
static inline
bool is_colliding(const   Line_Model_Tag   &,
                  const   Circle_Model_Tag &,
                  vec_t   lpoint,
                  vec_t   ldirection,
                  vec_t   rcentre,
                  float_t rradius)
{
  auto altitude = rcentre - math::intersection_point(lpoint, ldirection, rcentre, { -ldirection.y, ldirection.x });

  return math::length_sq(altitude) <= rradius * rradius;
}

/**
 * Ray x Ray
 */
static inline
bool is_colliding(const Ray_Model_Tag &,
                  const Ray_Model_Tag &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rpoint,
                  vec_t rdirection)
{
  if (math::is_parallel(ldirection, rdirection))
    return is_colliding(point_model_tag, line_model_tag, lpoint, rpoint, rdirection);

  vec_t cross = math::intersection_point(lpoint, ldirection, rpoint, rdirection);

  if ( math::diff_dir_approx(cross - lpoint, ldirection)
    || math::diff_dir_approx(cross - rpoint, rdirection))
  {
    return false;
  }

  return true;
}

/**
 * Ray x Segment
 */

static inline
bool is_colliding(const Ray_Model_Tag     &,
                  const Segment_Model_Tag &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rbegin_point,
                  vec_t rend_point)
{
  if (math::is_parallel(ldirection, rbegin_point - rend_point))
    return !math::is_parallel(ldirection, rbegin_point - lpoint);

  auto cross = math::intersection_point(lpoint, ldirection, rbegin_point, rend_point - rbegin_point);

  if (math::same_dir_approx_i(cross - lpoint, ldirection))
    return true;

  return math::same_dir_approx_i(cross - rbegin_point, cross - rend_point);
}

/**
 * Ray x Box
 */
static inline
bool is_colliding(const Ray_Model_Tag &,
                  const Box_Model_Tag &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rcentre,
                  vec_t rborder)
{
  const vec_t vertices[] =
  { { rcentre.x - rborder.x, rcentre.y + rborder.y }
  , { rcentre.x + rborder.x, rcentre.y + rborder.y }
  , { rcentre.x + rborder.x, rcentre.y - rborder.y }
  , { rcentre.x - rborder.x, rcentre.y - rborder.y } };

  if ( is_colliding(ray_model_tag, segment_model_tag, lpoint, ldirection, vertices[0], vertices[1])
    || is_colliding(ray_model_tag, segment_model_tag, lpoint, ldirection, vertices[1], vertices[2])
    || is_colliding(ray_model_tag, segment_model_tag, lpoint, ldirection, vertices[2], vertices[3])
    || is_colliding(ray_model_tag, segment_model_tag, lpoint, ldirection, vertices[3], vertices[0]))
  {
    return true;
  }

  return false;
}

/**
 * Ray x Circle
 */
static inline
bool is_colliding(const   Ray_Model_Tag    &,
                  const   Circle_Model_Tag &,
                  vec_t   lpoint,
                  vec_t   ldirection,
                  vec_t   rcentre,
                  float_t rradius)
{
  if (math::is_inside(lpoint, rcentre, rradius))
    return true;

  vec_t cross = math::intersection_point(lpoint, ldirection, rcentre, { -ldirection.y, ldirection.x });

  if (math::same_dir_approx_i(cross - lpoint, ldirection))
    return true;

  return false;
}

/**
 * Segment x Segment
 */
static inline
bool is_colliding(const Segment_Model_Tag &,
                  const Segment_Model_Tag &,
                  vec_t lbegin_point,
                  vec_t lend_point,
                  vec_t rbegin_point,
                  vec_t rend_point)
{
  // TODO: math::is_intersect 2016-03-11 19:48:25
  return math::is_intersect(lbegin_point, lend_point, rbegin_point, rend_point);
}

/**
 * Segment_Model_Tag & Box_Model_Tag
 */
static inline
bool is_colliding(const Segment_Model_Tag &,
                  const Box_Model_Tag     &,
                  vec_t lbegin_point,
                  vec_t lend_point,
                  vec_t rcentre,
                  vec_t rborder)
{
  if ( is_colliding(point_model_tag, box_model_tag, lbegin_point, rcentre, rborder)
    || is_colliding(point_model_tag, box_model_tag, lend_point, rcentre, rborder))
  {
    return true;
  }

  const vec_t vertices[] =
  { { rcentre.x - rborder.x, rcentre.y + rborder.y }
  , { rcentre.x + rborder.x, rcentre.y + rborder.y }
  , { rcentre.x + rborder.x, rcentre.y - rborder.y }
  , { rcentre.x - rborder.x, rcentre.y - rborder.y } };

  if ( is_colliding(segment_model_tag, segment_model_tag, lbegin_point, lend_point, vertices[0], vertices[1])
    || is_colliding(segment_model_tag, segment_model_tag, lbegin_point, lend_point, vertices[1], vertices[2])
    || is_colliding(segment_model_tag, segment_model_tag, lbegin_point, lend_point, vertices[2], vertices[3])
    || is_colliding(segment_model_tag, segment_model_tag, lbegin_point, lend_point, vertices[3], vertices[0]))
  {
    return true;
  }

  return false;
}

/**
 * Segment x Circle
 */
static inline
bool is_colliding(const   Segment_Model_Tag &,
                  const   Circle_Model_Tag  &,
                  vec_t   lbegin_point,
                  vec_t   lend_point,
                  vec_t   rcentre,
                  float_t rradius)
{
  if ( math::is_inside(lbegin_point, rcentre, rradius)
    || math::is_inside(lend_point, rcentre, rradius))
  {
    return true;
  }

  if ( is_colliding(ray_model_tag, circle_model_tag, lbegin_point, lend_point - lbegin_point, rcentre, rradius)
    && is_colliding(ray_model_tag, circle_model_tag, lend_point, lbegin_point - lend_point, rcentre, rradius))
  {
    return true;
  }

  return false;
}

/**
 * Box x Box
 */
static inline
bool is_colliding(const Box_Model_Tag &,
                  const Box_Model_Tag &,
                  vec_t lcentre,
                  vec_t lborder,
                  vec_t rcentre,
                  vec_t rborder)
{
  if ( lcentre.x + lborder.x < rcentre.x - rborder.x
    || lcentre.x - lborder.x > rcentre.x + rborder.x
    || lcentre.y + lborder.y < rcentre.y - rborder.y
    || lcentre.y - lborder.y > rcentre.y + rborder.y)
  {
    return false;
  }

  return true;
}

/**
 * Box x Circle
 */
static inline
bool is_colliding(const   Box_Model_Tag    &,
                  const   Circle_Model_Tag &,
                  vec_t   lcentre,
                  vec_t   lborder,
                  vec_t   rcentre,
                  float_t rradius)
{
  // XXX: 2016-03-08 08:22:50
  const vec_t vertices[] =
  { { lcentre.x - lborder.x, lcentre.y + lborder.y }
  , { lcentre.x + lborder.x, lcentre.y + lborder.y }
  , { lcentre.x + lborder.x, lcentre.y - lborder.y }
  , { lcentre.x - lborder.x, lcentre.y - lborder.y } };

  if ( is_colliding(point_model_tag, circle_model_tag, vertices[0], rcentre, rradius)
    || is_colliding(point_model_tag, circle_model_tag, vertices[1], rcentre, rradius)
    || is_colliding(point_model_tag, circle_model_tag, vertices[2], rcentre, rradius)
    || is_colliding(point_model_tag, circle_model_tag, vertices[3], rcentre, rradius))
  {
    return true;
  }

  if ( is_colliding(segment_model_tag, circle_model_tag, vertices[0], vertices[1], rcentre, rradius)
    || is_colliding(segment_model_tag, circle_model_tag, vertices[1], vertices[2], rcentre, rradius)
    || is_colliding(segment_model_tag, circle_model_tag, vertices[2], vertices[3], rcentre, rradius)
    || is_colliding(segment_model_tag, circle_model_tag, vertices[3], vertices[0], rcentre, rradius))
  {
    return true;
  }

  auto rdir = glm::normalize(rcentre - lcentre) * rradius;

  return is_colliding(point_model_tag, box_model_tag, rdir, lcentre, lborder);
}

/**
 * Circle x Circle
 */
static inline
bool is_colliding(const   Circle_Model_Tag &,
                  const   Circle_Model_Tag &,
                  vec_t   lcentre,
                  float_t lradius,
                  vec_t   rcentre,
                  float_t rradius)
{
  return math::length_sq(lcentre - rcentre) <= lradius * lradius + rradius * rradius;
}


template <class M1, class M2, bool = (uint32_t(M1::prio::value) < uint32_t(M2::prio::value))>
struct Collision_Test_Dispatch_Helper
{
  template <class ...Args>
  static inline
  bool apply(const M1   &m1,
             const M2   &m2,
             const Args &...args)
  {
    return is_colliding(m1, m2, args...);
  }
};

template <unsigned N>
struct Shift2;

template <>
struct Shift2<0u>
{
  template <class M1, class M2, typename ...Args>
  static inline
  bool apply(const M1   &m1,
             const M2   &m2,
             const Args &...args)
  {
    return is_colliding(m1, m2, args...);
  }
};

template <unsigned N>
struct Shift2
{
  template <class M1, class M2, typename A1, typename ...Args>
  static inline
  bool apply(const M1   &m1,
             const M2   &m2,
             const A1   &a1,
             const Args &...args)
  {
    return Shift2<N - 1>::template apply(m1, m2, args..., a1);
  }
};

template <class M1, class M2>
struct Collision_Test_Dispatch_Helper<M1, M2, false>
{

  template <class ...Args>
  static inline
  bool apply(const M1   &m1,
             const M2   &m2,
             const Args &...args)
  {
    return Shift2<M1::take::value>::template apply(m2, m1, args...);
  }
};

} // namespace details

// XXX: 2016-03-12 15:16:17
template <class M1, class M2, class ...Args>
static inline bool is_colliding(const M1   &m1,
                                const M2   &m2,
                                const Args &...args)
{
  return details::Collision_Test_Dispatch_Helper<M1, M2>::template apply(m1, m2, args...);
}

} // namespace Xi

#endif // COLLISION_H_INCLUDED_I9WTG7HW


