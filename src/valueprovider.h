#ifndef VALUEPROVIDER_H_INCLUDED_JUOWERCO
#define VALUEPROVIDER_H_INCLUDED_JUOWERCO

#include "actor.h"

namespace Xi {

// TODO: auto derive. 2016-03-16 18:47:03

class Value_Provider : public Extends<Actor>
{
public:
  virtual float_t get_position_value()     const { return 0; }
  virtual float_t get_velocity_value()     const { return 0; }
  virtual float_t get_acceleration_value() const { return 0; }
};

} // namespace Xi

#endif // end of include guard: VALUEPROVIDER_H_INCLUDED_JUOWERCO

