#ifndef MOVEMENT_H_INCLUDED_TNLMQZKI
#define MOVEMENT_H_INCLUDED_TNLMQZKI

#include "common.h"

namespace Xi {

class Movement : public Actor
{
  using Super = Actor;

  XIC_EXPORT(f, change_value, duration, limit_value)
  XIC_EXPORT(u, curve_type, finish_policy)

private:
  virtual Phy_Status do_update(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: MOVEMENT_H_INCLUDED_TNLMQZKI

