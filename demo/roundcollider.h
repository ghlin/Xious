#ifndef ROUNDCOLLIDER_H_INCLUDED_6OERUDRS
#define ROUNDCOLLIDER_H_INCLUDED_6OERUDRS

#include "demo.h"

namespace Xi {

class Round_Collider : public Collider
{
public:
  Collision_Model_Type get_collision_model_type() const override
  {
    return Collision_Model_Type::CM_Round;
  }

  Collision_Model get_collision_model() const override
  {
    return Collision_Model { CM_Round, { Round_Model { 2.0f } } };
  }
protected:
  virtual void update_logic(const Update_Details &) override { }
};

} // namespace Xi


#endif // end of include guard: ROUNDCOLLIDER_H_INCLUDED_6OERUDRS

