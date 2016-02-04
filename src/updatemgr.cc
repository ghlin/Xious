#include "updatemgr.h"
#include "updatedetails.h"
#include "entity.h"

namespace Xi {

void Update_Group::update_event(Instance *instance,
                                float_t   dt)
{
  Update_Details ud;

  for (auto *obj : members)
  {
    auto *entity = static_cast<Entity *>(obj);
    auto *event  = static_cast<Event_Component *>(entity->query_component(CID_State_Evt));

    ud.self = entity;
    ud.delta_time_elpased = dt;

    event->update(ud);
  }
}

void Update_Group::update_phy(Instance *instance,
                              float_t   dt)
{
  Update_Details ud;

  for (auto *obj : members)
  {
    auto *entity = static_cast<Entity *>(obj);
    auto *phy    = entity->phy_component();
    auto *colli  = entity->query_component(CID_Collision_Evt);

    ud.self = entity;
    ud.delta_time_elpased = dt;

    auto xyv = phy->update(ud);
    // use colli;
  }
}

void Update_Group::update(Instance *instance,
                          float_t   dt)
{
  update_phy(instance, dt);
  update_event(instance, dt);
}

} // namespace Xi

