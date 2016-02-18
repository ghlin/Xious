#ifndef ROUNDCOLLIDER_H_INCLUDED_GMSOAYXJ
#define ROUNDCOLLIDER_H_INCLUDED_GMSOAYXJ

#include "../src/collider.h"

namespace Xi {

class Round_Collider : public Collider
{
  using Super = Collider;

  Collision_Model collision_model;
public:
  Round_Collider(float_t radius)
    : collision_model({ CM_Round, Round_Model { radius } })
  { }

  virtual Collision_Model_Type get_collision_model_type() const override final
  {
    return CM_Round;
  }

  virtual Collision_Model get_collision_model() const override final
  {
    return collision_model;
  }
};

} // namespace Xi

#endif // end of include guard: ROUNDCOLLIDER_H_INCLUDED_GMSOAYXJ

