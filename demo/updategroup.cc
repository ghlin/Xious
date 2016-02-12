#include "demo.h"
#include "updategroup.h"
#include "render.h"


namespace Xi {

static inline
bool update_routine(Handle<Entity> &entity,
                    Update_Details  ud)
{
  ud.focus = entity.get();


  entity->update(ud);

  auto position = entity->get_position();

  if (entity->state == ES_To_Remove)
  {
    return true;
  }


  if (entity->flags | Die_If_Move_Off_Screen)
  {
    if (!math::is_inside(entity->get_position(),
                         { 0, 0 },
                         { ud.border.ws, ud.border.hs }))
    {
      entity->state = ES_To_Remove;
    }
  }

  return false;
}

void Update_Group::update_logic(const Update_Details &ud)
{
  entities.remove_if([ud] (auto &e) { return update_routine(e, ud); });
}

void Update_Group::draw(Draw_Details dd)
{
  for (auto &&e : entities)
  {
    dd.focus = e.get();
    e->render->draw(dd);
  }
}

} // namespace Xi

