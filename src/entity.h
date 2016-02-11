#ifndef ENTITY_H_INCLUDED_QS1YHTJM
#define ENTITY_H_INCLUDED_QS1YHTJM

#include "particle.h"
#include "collider.h"

namespace Xi {

enum Entity_Status
{
  Spawning,     ///< 正在创生
  Dying,        ///< 正在消灭(如超出屏幕范围)
  Normal,       ///< 参与正常更新
  Destroying,   ///< 正在消灭(参与碰撞导致的消灭)
};

class Entity : public Particle
{
protected:
  Handle<Collider> collider;

  uint32_t         layer,
                   state,
                   update_group,
                   collision_group;

  XI_PROP_EXPORT( (Collider, collider)
                , (Layer, layer)
                , (State, state)
                , (Update_Group, update_group)
                , (Collision_Group, collision_group)
                );
public:
  Entity(Handle<Collider> collider,
         uint32_t         layer,
         uint32_t         state,
         uint32_t         update_group,
         uint32_t         collision_group)
    : collider(std::move(collider))
    , layer(layer)
    , update_group(update_group)
    , collision_group(collision_group)
  { }

  const Collider *get_collider() const
  {
    return collider.get();
  }
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_QS1YHTJM

