#define XI_COLLISION_DEBUG

#include "collision.h"
#include "test.h"

namespace Xi {

namespace details {

static inline Str extract_type(const Str &full)
{
  return u_map<std::basic_string>(full.substr(0, full.length() - sizeof ("_model_tag") + 1),
                                  [] (auto ch) { return (char)std::toupper(ch); });
}

static inline Str token(const Str &lhs, const Str &rhs)
{
  return lhs + " x " + rhs;
}

} // namespace details

#define token(m1, m2) details::token(details::extract_type(XI_STRINGIFY(m1)), details::extract_type(XI_STRINGIFY(m2)))

#define TEST(hit_or_not, m1, m2, ...)                   \
  XI_UNIT_TEST_CASE(token(m1, m2)) {                    \
    auto colliding = is_colliding(m1, m2, __VA_ARGS__); \
    auto result    = colliding == (hit_or_not);         \
    XI_UT_EXPECT(result);                               \
  }

XI_UNIT_TEST_SCOPE
{
  auto v = [] (auto x, auto y) { return vec_t { x, y }; };
  constexpr bool hit = true, mis = false;

  TEST(hit, point_model_tag, point_model_tag, v(0, 0), v(0, 0));
  TEST(hit, point_model_tag, line_model_tag, v(0, 0), v(-1, -1), v(1, 1));
  TEST(hit, line_model_tag, point_model_tag, v(-1, -1), v(1, 1), v(0, 0));
  TEST(hit, line_model_tag, line_model_tag, v(0, 0), v(1, 1), v(1, 0), v(-1, 1));
  TEST(hit, line_model_tag, ray_model_tag, v(0, 0), v(1, 1), v(1, 0), v(-1, 1));
  TEST(hit, ray_model_tag, ray_model_tag, v(0, 0), v(1, 1), v(1, 0), v(-1, 1));
  TEST(hit, ray_model_tag, ray_model_tag, v(0, 0), v(1000, 1), v(1, 0), v(-1000, 1));
  TEST(hit, ray_model_tag, circle_model_tag, v(-100, 100), v(1, 0), v(0, 0), 100);
  TEST(hit, circle_model_tag, ray_model_tag, v(0, 0), 100, v(-100, 100), v(1, 0));
  TEST(mis, circle_model_tag, ray_model_tag, v(0, 0), 100, v(100, 100), v(1, 0));
  TEST(mis, circle_model_tag, box_model_tag, v(0, 0), 100, v(100, 100), v(5, 5));

  auto sqrt_2 = std::sqrt(2);
  TEST(hit, circle_model_tag, box_model_tag, v(0, 0), 100, v(50 * sqrt_2 / 2, 50 * sqrt_2 / 2), v(10, 10));

  TEST(hit, box_model_tag, segment_model_tag, v(0, 0), v(5, 5), v(3, 3), v(4, 4));
  TEST(hit, box_model_tag, segment_model_tag, v(0, 0), v(5, 5), v(3, 3), v(40, 40));
  TEST(hit, box_model_tag, segment_model_tag, v(0, 0), v(5, 5), v(-30, 3), v(30, 4));
  TEST(hit, point_model_tag, ray_model_tag, v(0, 0), v(-1, -1), v(1, 1));
  TEST(mis, point_model_tag, ray_model_tag, v(0, 0), v(1, 1), v(1, 1));
  TEST(hit, ray_model_tag, point_model_tag, v(-1, -1), v(1, 1), v(0, 0));
  TEST(mis, ray_model_tag, point_model_tag, v(1, 1), v(1, 1), v(0, 0));
}

} // namespace Xi

