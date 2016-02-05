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

class Entity : public Pooled_Object
{
  friend class Entity_Ctrl;

  Component *components[kComponents];
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
  Phy_Component *phy_component()
  {
    return static_cast<Phy_Component *>(query_component(CID_Phy_Update));
  }

  inline
  const Phy_Component *phy_component() const
  {
    return static_cast<const Phy_Component *>(query_component(CID_Phy_Update));
  }
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_KCSPNGV9

