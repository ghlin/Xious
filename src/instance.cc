#ifndef INSTANCE_CC_INCLUDED_NHNLZOLK
#define INSTANCE_CC_INCLUDED_NHNLZOLK

#include "actor.h"
#include "objgroup.h"
#include "entity.h"
#include "instance.h"
#include "updatedetails.h"
#include "collision.h"


namespace Xi {

class Instance::Instance_Impl
{
public:
  Obj_Group        *player_entities,
                   *player_bullets,
                   *enemy_entities,
                   *enemy_bullets,
                   *bonus_items;
};

void Instance::update(float_t dt)
{
  Update_Details ud;

  ud.players[0]         = static_cast<Entity *>(pimpl->player_entities->members[0]);
  ud.delta_time_elpased = dt;
  ud.delta_frame        = 1;

  Obj_Group        *player_entities = pimpl->player_entities,
                   *player_bullets  = pimpl->player_bullets,
                   *enemy_entities  = pimpl->enemy_entities,
                   *enemy_bullets   = pimpl->enemy_bullets,
                   *bonus_items     = pimpl->bonus_items;

  for (auto &&e : player_bullets->members)
  {
    // 不作碰撞检测

    auto *entity = ud.self = static_cast<Entity *>(e);
    auto *actor  = static_cast<Actor *>(entity->get_actor());

    actor->update(ud);
  }

  for (auto &&e : enemy_entities->members)
  {
    auto *entity = ud.self = static_cast<Entity *>(e);
    auto *actor  = static_cast<Actor *>(entity->get_actor());

    auto phy_status = actor->update(ud);

    for (auto &&p : player_bullets->members)
    {
      auto *bullet = static_cast<Entity *>(p);

      if (is_colliding(bullet, entity))
      {
        // TODO(ghlin) : 2016-02-08 21:14:49
      }
    }
  }
}

} // namespace Xi


#endif // end of include guard: INSTANCE_CC_INCLUDED_NHNLZOLK

