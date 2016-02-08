#ifndef ENTITY_H_INCLUDED_KCSPNGV9
#define ENTITY_H_INCLUDED_KCSPNGV9

#include "config.h"
#include "object.h"
#include "component.h"

namespace Xi {

class Entity : public X_Component<bool>
{
  using Super = X_Component<bool>;

  friend class Entity_Ctrl;

  XIC_EXPORT(v,
             init_postion,
             colli_centre,
             cm_bouding_box)

  XIC_EXPORT(u,
             life_ctrl_flags,
             collision_model,
             collision_group,
             entity_tag,
             update_group)

  XIC_EXPORT(f,
             cm_radius)

  XIC_EXPORT(x,
             actor,
             dir,
             render)
public:

private:
  bool do_update(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_KCSPNGV9

