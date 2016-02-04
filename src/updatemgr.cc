#include "updatemgr.h"
#include "updatedetails.h"
#include "entity.h"

namespace Xi {

void Phy_Update_Group::update(const Instance *instance,
                              float           dt)
{
  Update_Details ud;
  //TODO

  for (auto &obj : members)
  {
    auto *entity = static_cast<Entity *>(obj);

    ud.self = entity;

    auto xyv = entity->phy_component()->update(ud);

    // cgg->update(xyv, entity);
  }
}

} // namespace Xi

