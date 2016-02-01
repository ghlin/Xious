#ifndef ENTITY_H_INCLUDED_KCSPNGV9
#define ENTITY_H_INCLUDED_KCSPNGV9

#include "config.h"
#include "object.h"
#include "pattern.h"

namespace Xi {

class Entity : public Ref_Counted_Object
{
  Phy_Pattern *phy;
  Dir_Pattern *dir;
  Art_Pattern *art;
  Evt_Pattern *evt;
public:
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_KCSPNGV9

