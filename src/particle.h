#ifndef PARTICLE_H_INCLUDED_ZL9PMB1D
#define PARTICLE_H_INCLUDED_ZL9PMB1D

#include "actor.h"

namespace Xi {

class Particle : public Actor
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

#endif // end of include guard: PARTICLE_H_INCLUDED_ZL9PMB1D

