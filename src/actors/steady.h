#ifndef STEADY_H_INCLUDED_QGY5UKJH
#define STEADY_H_INCLUDED_QGY5UKJH

#include "../actor.h"

namespace Xi {

class Steady : public Actor
{
  using Super = Actor;

  virtual Phy_Status do_update(const Update_Details &ud) override final;

  XIC_EXPORT(v, at)
};

} // namespace Xi

#endif // end of include guard: STEADY_H_INCLUDED_QGY5UKJH

