#ifndef MOVEMENT_H_INCLUDED_TNLMQZKI
#define MOVEMENT_H_INCLUDED_TNLMQZKI

#include "common.h"

namespace Xi {

class Movement : public Actor
{
  using Super = Actor;

public:
  enum Curve_Type : param_u_value_t
  {
    U_Linear,
    U_Quadratic,
    U_Cubic,
    U_Quartic,
    U_Quintic,
    U_Sinusoidal,
    U_Exponential
  };

  enum Finish_Policy : param_u_value_t
  {
    U_Continue,
    U_Stop,
    U_Reset,
  };

  XIC_EXPORT(f, change_value, duration, limit_value)
  XIC_EXPORT(u, curve_type, finish_policy)

public:
  virtual bool finished() const override;
private:
  virtual Phy_Status do_update(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: MOVEMENT_H_INCLUDED_TNLMQZKI

