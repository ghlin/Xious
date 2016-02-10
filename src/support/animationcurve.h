#ifndef ANIMATIONCURVE_H_INCLUDED_SOQN6ZJK
#define ANIMATIONCURVE_H_INCLUDED_SOQN6ZJK

#include "../config.h"

namespace Xi { namespace curve {

struct Linear
{
  static inline
  vec_t update(float_t time_elpased,
               float_t duration,
               float_t change_value)
  {
    return { time_elpased / duration * change_value
           , change_value / duration };
  }
};

struct Quadratic
{
  static inline
  vec_t update(float_t time_elpased,
               float_t duration,
               float_t change_value)
  {
    auto x = time_elpased / duration;

    return { change_value * x * x
           , change_value * x * 2 / duration };
  }
};

struct Cubic
{
  static inline
  vec_t update(float_t time_elpased,
               float_t duration,
               float_t change_value)
  {
    auto x = time_elpased / duration;

    return { change_value * x * x * x
           , change_value * x * x * 3 / duration };
  }
};

struct Quartic
{
  static inline
  vec_t update(float_t time_elpased,
               float_t duration,
               float_t change_value)
  {
    auto x = time_elpased / duration;

    return { change_value * x * x * x * x
           , change_value * x * x * x * 4 / duration };
  }
};

struct Quintic
{
  static inline
  vec_t update(float_t time_elpased,
               float_t duration,
               float_t change_value)
  {
    auto x = time_elpased / duration;

    return { change_value * x * x * x * x * x
           , change_value * x * x * x * x * 5 / duration };
  }
};

struct Sinusoidal
{
  static inline
  vec_t update(float_t time_elpased,
              float_t duration,
              float_t change_value)
  {
    // sin 0              -> 0
    // sin PI / 2         -> 1
    // f : [0, 1] -> [0, PI / 2]

    return { change_value * std::sin(time_elpased / duration * M_PI / 2)
           , change_value / duration * M_PI / 2 * std::cos(time_elpased / duration * M_PI / 2) };
  }
};

struct Exponential
{
  static inline
  vec_t update(float_t time_elpased,
              float_t duration,
              float_t change_value)
  {
    // TODO(ghlin) : 指数型缓动 2016-02-07 15:05:49
    return { };
  }
};

template <class T>
static inline
vec_t ease_in(float_t time_elpased,
              float_t duration,
              float_t change_value)
{
  return T::update(time_elpased, duration, change_value);
}

template <class T>
static inline
vec_t ease_out(float_t time_elpased,
               float_t duration,
               float_t change_value)
{
  return T::update(duration - time_elpased, duration, change_value);
}

template <class T>
static inline
vec_t ease_in_out(float_t time_elpased,
                  float_t duration,
                  float_t change_value)
{
  if (time_elpased > duration / 2)
    return ease_out<T>(time_elpased - duration, duration / 2, change_value);
  else
    return ease_in<T>(time_elpased, duration / 2, change_value);
}

} // namespace curve
} // namespace Xi

#endif // end of include guard: ANIMATIONCURVE_H_INCLUDED_SOQN6ZJK

