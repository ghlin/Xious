#ifndef PHYSTATUS_H_INCLUDED_HURXKEZA
#define PHYSTATUS_H_INCLUDED_HURXKEZA

#include "config.h"

namespace Xi {

struct Phy_Status
{
  vec2       position;
  vec2       velocity;

  inline
  Phy_Status &operator +=(const Phy_Status &rhs)
  {
    position += rhs.position;
    velocity += rhs.velocity;

    return *this;
  }

  inline
  Phy_Status &operator -=(const Phy_Status &rhs)
  {
    position -= rhs.position;
    velocity -= rhs.velocity;

    return *this;
  }

  inline
  Phy_Status operator +(const Phy_Status &rhs) const
  {
    return { position + rhs.position, velocity + rhs.velocity };
  }

  inline
  Phy_Status operator -(const Phy_Status &rhs) const
  {
    return { position - rhs.position, velocity - rhs.velocity };
  }

  inline
  Phy_Status &operator *=(float_t factor)
  {
    position *= factor;
    velocity *= factor;

    return *this;
  }

  inline
  Phy_Status &operator /=(float_t factor)
  {
    position /= factor;
    velocity /= factor;

    return *this;
  }
};

} // namespace Xi


#endif // end of include guard: PHYSTATUS_H_INCLUDED_HURXKEZA

