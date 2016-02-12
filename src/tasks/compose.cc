#include "compose.h"

namespace Xi {

void Composed_Task::update_logic(const Update_Details &ud)
{
  position = {};
  velocity = {};

  for (auto &&sub : tasks)
  {
    sub->update(ud);
    position += sub->get_position();
    velocity += sub->get_velocity();
  }
}

Handle<Prototype> Composed_Task::clone() const
{
  return std::make_shared<Composed_Task>(u_map(tasks,
                                               [] (const auto &task)
                                               {
                                                 return std::static_pointer_cast<Task>(task->clone());
                                               }));
}

} // namespace Xi

