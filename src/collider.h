#ifndef COLLIDER_H_INCLUDED_PLHE3SVG
#define COLLIDER_H_INCLUDED_PLHE3SVG

#include "actor.h"
#include "support/collisionmodel.h"

namespace Xi {

class Collider : public Extends<Actor>
{
  struct Colli_Pack
  {
    const Collider *collider;
    vec_t           pos;
  };

  static inline
  bool _fwd_round(const Colli_Pack &lhs, const Colli_Pack &rhs)
  {
    auto lmod = lhs.collider->get_collision_model();
    auto rmod = rhs.collider->get_collision_model();
    auto lpos = lhs.pos;
    auto rpos = rhs.pos;

    switch (rhs.collider->get_collision_model_type())
    {
    case CM_Round:    return Xi::is_colliding(lpos, lmod.round, rpos, rmod.round);
    case CM_Box:      return Xi::is_colliding(lpos, lmod.round, rpos, rmod.box);
    case CM_Segment:  return Xi::is_colliding(lpos, lmod.round, rpos, rmod.segment);
    case CM_Line:     return Xi::is_colliding(lpos, lmod.round, rpos, rmod.line);
    default:
      Xi_die("_fwd_round wrong order.");
      return false;
    }
  }

  static inline
  bool _fwd_box(const Colli_Pack &lhs, const Colli_Pack &rhs)
  {
    auto lmod = lhs.collider->get_collision_model();
    auto rmod = rhs.collider->get_collision_model();
    auto lpos = lhs.pos;
    auto rpos = rhs.pos;

    switch (rhs.collider->get_collision_model_type())
    {
    case CM_Box:      return Xi::is_colliding(lpos, lmod.box, rpos, rmod.box);
    case CM_Segment:  return Xi::is_colliding(lpos, lmod.box, rpos, rmod.segment);
    case CM_Line:     return Xi::is_colliding(lpos, lmod.box, rpos, rmod.line);
    default:
      Xi_die("_fwd_box wrong order.");
      return false;
    }
  }

  static inline
  bool _fwd_segment(const Colli_Pack &lhs, const Colli_Pack &rhs)
  {
    auto lmod = lhs.collider->get_collision_model();
    auto rmod = rhs.collider->get_collision_model();
    auto lpos = lhs.pos;
    auto rpos = rhs.pos;

    switch (rhs.collider->get_collision_model_type())
    {
    case CM_Segment:  return Xi::is_colliding(lpos, lmod.segment, rpos, rmod.segment);
    case CM_Line:     return Xi::is_colliding(lpos, lmod.segment, rpos, rmod.line);
    default:
      Xi_die("_fwd_segment wrong order.");
      return false;
    }
  }

  static inline
  bool _fwd_line(const Colli_Pack &lhs, const Colli_Pack &rhs)
  {
    auto lmod = lhs.collider->get_collision_model();
    auto rmod = rhs.collider->get_collision_model();
    auto lpos = lhs.pos;
    auto rpos = rhs.pos;

    switch (rhs.collider->get_collision_model_type())
    {
    case CM_Line:     return Xi::is_colliding(lpos, lmod.line, rpos, rmod.line);
    default:
      Xi_die("_fwd_line wrong order.");
      return false;
    }
  }

public:
  virtual Collision_Model_Type get_collision_model_type() const = 0;
  virtual Collision_Model      get_collision_model()      const = 0;

  inline bool is_colliding(const vec_t    &this_pos,
                           const Collider *another,
                           const vec_t    &another_pos) const
  {
    Xi_debug_check(!(get_collision_model_type() == CM_Special && another->get_collision_model_type() == CM_Special));

    if (get_collision_model_type() == CM_Special)
    {
      return special_colliding_logic(this_pos,
                                     another,
                                     another_pos);
    }

    if (another->get_collision_model_type() == CM_Special)
    {
      return another->special_colliding_logic(another_pos,
                                              this,
                                              this_pos);
    }

    auto lhs = get_collision_model_type() > another->get_collision_model_type()
      ? Colli_Pack { this, this_pos }
      : Colli_Pack { another, another_pos };

    auto rhs = get_collision_model_type() > another->get_collision_model_type()
      ? Colli_Pack { another, another_pos }
      : Colli_Pack { this, this_pos };


    switch (lhs.collider->get_collision_model_type())
    {
    case CM_Round:    return _fwd_round(lhs, rhs);
    case CM_Box:      return _fwd_box(lhs, rhs);
    case CM_Segment:  return _fwd_segment(lhs, rhs);
    case CM_Line:     return _fwd_line(lhs, rhs);
    default:
      Xi_die("impossible.");
      return false;
    }
  }
protected:
  virtual bool special_colliding_logic(const vec_t    &this_pos,
                                       const Collider *another,
                                       const vec_t    &another_pos) const;

};

} // namespace Xi


#endif // end of include guard: COLLIDER_H_INCLUDED_PLHE3SVG

