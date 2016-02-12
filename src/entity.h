#ifndef ENTITY_H_INCLUDED_QS1YHTJM
#define ENTITY_H_INCLUDED_QS1YHTJM

#include "particle.h"

namespace Xi {

enum Entity_Status
{
  ES_Spawning,     ///< 正在创生
  ES_Dying,        ///< 正在消灭(如超出屏幕范围)
  ES_Normal,       ///< 参与正常更新
  ES_Destroying,   ///< 正在消灭(参与碰撞导致的消灭)
  ES_To_Remove,    ///< 指示移除
};

class Entity : public Particle
{
  using Super = Particle;
public:
  Handle<Collider> collider;
  Handle<Render>   render;

  uint32_t         layer,
                   state,
                   update_group,
                   collision_group;

  XI_PROP_EXPORT( (Collider, collider)
                , (Layer, layer)
                , (State, state)
                , (Update_Group, update_group)
                , (Collision_Group, collision_group)
                , (Render, render)
                );
public:
  Entity() { }

  Entity(Handle<Collider> collider,
         Handle<Render>   render,
         uint32_t         layer,
         uint32_t         update_group,
         uint32_t         collision_group)
    : collider(std::move(collider))
    , render(std::move(render))
    , layer(layer)
    , state(ES_Spawning)
    , update_group(update_group)
    , collision_group(collision_group)
  { }

  const Collider *get_collider() const
  {
    return collider.get();
  }

  const Render  *get_render() const
  {
    return render.get();
  }
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_QS1YHTJM

