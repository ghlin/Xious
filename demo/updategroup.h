#ifndef UPDATEGROUP_H_INCLUDED_ZPUA3OCL
#define UPDATEGROUP_H_INCLUDED_ZPUA3OCL

#include "demo.h"

namespace Xi {

enum Update_Flags
{
  Die_If_Move_Off_Screen = 0x1,
};

class Update_Group : public Actor
{
  using Super = Actor;
protected:
  std::list<Handle<Entity>> entities;

  XI_PROP_EXPORT( (Entities, entities)
                , (Entities_Count, entities.size(), RO)
                );
public:
  inline size_t entities_count() const
  {
    return entities.size();
  }

  inline void push_back(Handle<Entity> entity)
  {
    entities.push_back(entity);
  }

  void draw(Draw_Details dd);
protected:
  virtual void update_logic(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: UPDATEGROUP_H_INCLUDED_ZPUA3OCL

