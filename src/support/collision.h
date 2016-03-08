#ifndef COLLISION_H_INCLUDED_I9WTG7HW
#define COLLISION_H_INCLUDED_I9WTG7HW

#include "../config.h"
#include "../util/math.h"


namespace Xi {

constexpr bool colli_debug_on =
#ifdef XI_COLLISION_DEBUG
  true
#else
  false
#endif
  ;

#define on_debug Xi_debug_if (colli_debug_on)

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
  };

  union {
    vec_t   direction;
    vec_t   end_point;
    vec_t   border;
    float_t radius;
  };
};

struct Collision_Model
{
  Collision_Model_Type type;
  Collision_Model_Data data;
};

template <uint32_t E>
struct Model_Tag
{
  enum : uint32_t { prio = E };
};

using Point_Model_Tag   = Model_Tag<CMT_Point>;
using Line_Model_Tag    = Model_Tag<CMT_Line>;
using Ray_Model_Tag     = Model_Tag<CMT_Ray>;
using Segment_Model_Tag = Model_Tag<CMT_Segment>;
using Box_Model_Tag     = Model_Tag<CMT_Box>;
using Circle_Model_Tag  = Model_Tag<CMT_Circle>;

constexpr static Point_Model_Tag   point_model_tag   = { };
constexpr static Line_Model_Tag    line_model_tag    = { };
constexpr static Ray_Model_Tag     ray_model_tag     = { };
constexpr static Segment_Model_Tag segment_model_tag = { };
constexpr static Box_Model_Tag     box_model_tag     = { };
constexpr static Circle_Model_Tag  circle_model_tag  = { };

/**
 * Point_Model_Tag x Point_Model_Tag
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
 * Point_Model_Tag x Line_Model_Tag
 */
static inline
bool is_colliding(const Point_Model_Tag &,
                  const Line_Model_Tag  &,
                  vec_t lpoint,
                  vec_t rpoint,
                  vec_t rdirection)
{
  on_debug
  {
    Xi_log("checking (%f, %f) on (%f, %f) (%f %f)",
           lpoint.x, lpoint.y,
           rpoint.x, rpoint.y, rdirection.x, rdirection.y);

    auto C = math::cross_product(rpoint - lpoint, rdirection);
    Xi_log(" cross -> %f", C);
  }

  return math::is_zero(math::cross_product(rpoint - lpoint, rdirection));
}

/**
 * Point_Model_Tag x Ray_Model_Tag
 */
static inline
bool is_colliding(const Point_Model_Tag &,
                  const Ray_Model_Tag   &,
                  vec_t lpoint,
                  vec_t rpoint,
                  vec_t rdirection)
{
  on_debug
  {
    Xi_log("checking (%f, %f) on (%f, %f) (%f %f)",
           lpoint.x, lpoint.y,
           rpoint.x, rpoint.y, rdirection.x, rdirection.y);
  }

  return is_colliding(point_model_tag, line_model_tag, lpoint, rpoint, rdirection)
    &&   math::dot_product(rpoint - lpoint, rdirection) < 0;
}

/**
 * Point_Model_Tag x Segment_Model_Tag
 */
static inline
bool is_colliding(const Point_Model_Tag   &,
                  const Segment_Model_Tag &,
                  vec_t lpoint,
                  vec_t rbegin_point,
                  vec_t rend_point)
{
  return is_colliding(point_model_tag, ray_model_tag, lpoint, rbegin_point, rbegin_point - rend_point)
    &&   is_colliding(point_model_tag, ray_model_tag, lpoint, rbegin_point, rend_point - rbegin_point);
}

/**
 * Point_Model_Tag x Box_Model_Tag
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
 * Point_Model_Tag x Circle_Model_Tag
 */
static inline
bool is_colliding(const   Point_Model_Tag  &,
                  const   Circle_Model_Tag &,
                  vec_t   lpoint,
                  vec_t   rcentre,
                  float_t radius)
{
  auto r = rcentre - lpoint;

  return radius * radius >= r.x * r.x + r.y * r.y;
}

/**
 * Line_Model_Tag x Line_Model_Tag
 */
static inline
bool is_colliding(const Line_Model_Tag &,
                  const Line_Model_Tag &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rpoint,
                  vec_t rdirection)
{
  return math::is_parallel(ldirection, rdirection)
    &&  !math::is_parallel(ldirection, lpoint - rpoint);
}

/**
 * Line_Model_Tag x Ray_Model_Tag
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

  return math::cross_product(cross - lpoint, ldirection) <= 0;
}

/**
 * Line_Model_Tag x Segment_Model_Tag
 */
static inline
bool is_colliding(const Line_Model_Tag    &,
                  const Segment_Model_Tag &,
                  vec_t lpoint,
                  vec_t ldirection,
                  vec_t rbegin_point,
                  vec_t rend_point)
{
  if (math::is_parallel(ldirection, rbegin_point - rend_point))
    return !math::is_parallel(ldirection, rbegin_point - lpoint);

  auto cross = math::intersection_point(lpoint, ldirection, rbegin_point, rbegin_point - rend_point);

  return math::diff_sign(cross - rbegin_point, cross - rend_point);
}

/**
 * Line_Model_Tag x Box_Model_Tag
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
 * Line_Model_Tag x Circle_Model_Tag
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

  return altitude.x * altitude.x + altitude.y * altitude.y <= rradius * rradius;
}

/**
 * Ray_Model_Tag x Ray_Model_Tag
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

  if ( math::dot_product(cross - lpoint, ldirection) < 0
    || math::dot_product(cross - rpoint, rdirection) < 0)
  {
    return false;
  }

  return true;
}

/**
 * Ray_Model_Tag x Segment_Model_Tag
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

  auto cross = math::intersection_point(lpoint, ldirection, rbegin_point, rbegin_point - rend_point);

  if (math::cross_product(cross - lpoint, ldirection) > 0)
    return true;

  return math::diff_sign(cross - rbegin_point, cross - rend_point);
}

/**
 * Ray_Model_Tag x Box_Model_Tag
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
 * Ray_Model_Tag x Circle_Model_Tag
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

  if (math::cross_product(lpoint - cross, lnormal) < 0)
    return true;

  return false;
}

/**
 * Segment_Model_Tag x Segment_Model_Tag
 */
static inline
bool is_colliding(const Segment_Model_Tag &,
                  const Segment_Model_Tag &,
                  vec_t lbegin_point,
                  vec_t lend_point,
                  vec_t rbegin_point,
                  vec_t rend_point)
{
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
 * Segment_Model_Tag x Circle_Model_Tag
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

  if ( is_colliding(ray_model_tag, circle_model_tag, lbegin_point, lbegin_point - lend_point, rcentre, rradius)
    && is_colliding(ray_model_tag, circle_model_tag, lend_point, lend_point - lbegin_point, rcentre, rradius))
  {
    return true;
  }

  return false;
}

/**
 * Box_Model_Tag x Box_Model_Tag
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
 * Box_Model_Tag x Circle_Model_Tag
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
 * Circle_Model_Tag x Circle_Model_Tag
 */
static inline
bool is_colliding(const   Circle_Model_Tag &,
                  const   Circle_Model_Tag &,
                  vec_t   lcentre,
                  float_t lradius,
                  vec_t   rcentre,
                  float_t rradius)
{
  auto dist2 = lcentre - rcentre;

  return dist2.x * dist2.x + dist2.y * dist2.y <= lradius * lradius + rradius * rradius;
}



} // namespace Xi

#endif // COLLISION_H_INCLUDED_I9WTG7HW


