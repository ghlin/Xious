#ifndef ENTITY_H_INCLUDED_KCSPNGV9
#define ENTITY_H_INCLUDED_KCSPNGV9

#include "config.h"
#include "object.h"
#include "component.h"

namespace Xi {

constexpr size_t kComponents = 16;

constexpr object_id_t CID_Configs       = 0,
                      CID_Phy_Update    = 1,
                      CID_Dir_update    = 2,
                      CID_Collision_Evt = 3,
                      CID_State_Evt     = 4,
                      CID_Render        = 5;

class Entity : public Component
{
  using Super = Component;

  friend class Entity_Ctrl;

  Component *components[kComponents];

  XIC_EXPORT(u, collision_group, update_group, entity_tag)
public:
  inline
  Component *query_component(object_id_t cid)
  {
    return components[cid];
  }

  inline
  const Component *query_component(object_id_t cid) const
  {
    return components[cid];
  }

  inline
  Actor *get_actor()
  {
    return static_cast<Actor *>(query_component(CID_Phy_Update));
  }

  inline
  const Actor *get_actor() const
  {
    return static_cast<const Actor *>(query_component(CID_Phy_Update));
  }
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_KCSPNGV9

