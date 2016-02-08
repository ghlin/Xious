#include "collision.h"
#include "entity.h"
#include "actor.h"
#include "support/collisionmodel.h"

namespace Xi {

static inline 
const vec2 &get_pos(const Entity *e)
{
  return static_cast<const Actor *>(e->get_actor())->get_last_status().position;
}

bool is_colliding(const Entity *A,
                  const Entity *B)
{
  switch (A->get_collision_model())
  {
  case CM_Round:
    switch (B->get_collision_model())
    {
    case CM_Round:
      return is_colliding(Round_Model { A->get_cm_radius() },
                          get_pos(A),
                          Round_Model { B->get_cm_radius() },
                          get_pos(B));
    case CM_Bounding_Box:
      return is_colliding(Round_Model { A->get_cm_radius() },
                          get_pos(A),
                          Bounding_Box_Model { B->get_cm_bouding_box().x, B->get_cm_bouding_box().y },
                          get_pos(B));
    }
  case CM_Bounding_Box:
    switch (B->get_collision_model())
    {
    case CM_Round:
      return is_colliding(Round_Model { B->get_cm_radius() },
                          get_pos(B),
                          Round_Model { A->get_cm_radius() },
                          get_pos(A));
    case CM_Bounding_Box:
      return is_colliding(Bounding_Box_Model { A->get_cm_bouding_box().x, A->get_cm_bouding_box().y },
                          get_pos(A),
                          Bounding_Box_Model { B->get_cm_bouding_box().x, B->get_cm_bouding_box().y },
                          get_pos(B));
    }
  }

  return false;
}

} // namespace Xi

