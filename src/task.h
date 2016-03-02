#ifndef TASK_H_INCLUDED_5KI9LKLH
#define TASK_H_INCLUDED_5KI9LKLH

#include "actor.h"
#include "util/math.h"

namespace Xi {

class Task : public Extends<Controller>
{
public:
  vec_t          position;
  vec_t          velocity;

  inline vec_t get_position() const
  {
    return position;
  }

  inline vec_t get_velocity() const
  {
    return velocity;
  }

  XI_PROP_EXPORT( (Position, position)
                , (Velocity, velocity)
                , (Position_X, position.x)
                , (Position_Y, position.y)
                , (Velocity_X, velocity.x)
                , (Velocity_Y, velocity.y)
                , (Position_Angle, math::angle(position), RO)
                , (Velocity_Angle, math::angle(velocity), RO)
                );
};

} // namespace Xi

#endif // end of include guard: TASK_H_INCLUDED_5KI9LKLH

