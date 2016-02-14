#ifndef VALUEPROVIDER_H_INCLUDED_JUOWERCO
#define VALUEPROVIDER_H_INCLUDED_JUOWERCO

#include "actor.h"

namespace Xi {

class Value_Provider : public Actor
{
  using Super = Actor;
public:
  virtual float_t get_position_value()     const { return 0; }
  virtual float_t get_velocity_value()     const { return 0; }
  virtual float_t get_acceleration_value() const { return 0; }
};

} // namespace Xi

#endif // end of include guard: VALUEPROVIDER_H_INCLUDED_JUOWERCO

