#include "rotate.h"
#include <glm/gtx/rotate_vector.hpp>

namespace Xi {

void Rotate::update_logic(const Update_Details &ud)
{
  original->update(ud);
  angle->update(ud);

  auto original_position = original->get_position(),
       original_velocity = original->get_velocity();

  auto alpha             = angle->get_position_value();

  position = glm::rotate(original_position, alpha);
  velocity = glm::rotate(original_velocity, alpha);
}

} // namespace Xi

