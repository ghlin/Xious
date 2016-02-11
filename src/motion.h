#ifndef MOTION_H_INCLUDED_XCIO5A7S
#define MOTION_H_INCLUDED_XCIO5A7S

#include "actor.h"

namespace Xi {

class Motion : public Actor
{
  using Super = Actor;
protected:
  vec_t          position;
  vec_t          velocity;

  XI_PROP_EXPORT( (Position, position)
                , (Velocity, velocity)
                );
public:
  inline vec_t get_position() const
  {
    return position;
  }

  inline vec_t get_velocity() const
  {
    return velocity;
  }
};


} // namespace Xi

#endif // end of include guard: MOTION_H_INCLUDED_XCIO5A7S

