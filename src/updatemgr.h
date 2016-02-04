#ifndef UPDATEMGR_H_INCLUDED_R8LOJYST
#define UPDATEMGR_H_INCLUDED_R8LOJYST

#include "config.h"
#include "object.h"
#include "objgroup.h"


namespace Xi {

class Update_Group : Obj_Group
{
  Object *global_update;
  void update_phy(Instance *instance, float_t dt);
  void update_event(Instance *instance, float_t dt);
public:

  void update(Instance *instance, float_t dt);
};

} // namespace Xi


#endif // end of include guard: UPDATEMGR_H_INCLUDED_R8LOJYST

