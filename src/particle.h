#ifndef PARTICLE_H_INCLUDED_Y6JTAFLH
#define PARTICLE_H_INCLUDED_Y6JTAFLH

#include "motion.h"
#include "actor.h"

namespace Xi {

class Particle : public Actor
{
  using Super = Actor;
protected:

  XI_PROP_EXPORT( (Motion, motion)
                , (Actor, actor)
                , (Flags, flags)
                , (Tag, tag)
                );
public:
  Handle<Motion>      motion;
  Handle<Actor>       actor;
  uint32_t            flags = 0,
                      tag   = 0;

  Particle(Handle<Motion> motion,
           Handle<Actor>  actor,
           uint32_t       flags,
           uint32_t       tag)
    : motion(std::move(motion))
    , actor(std::move(actor))
    , flags(flags)
    , tag(tag)
  { }


  inline vec_t get_position() const
  {
    return motion->get_position();
  }

  inline vec_t get_velocity() const
  {
    return motion->get_velocity();
  }

protected:
  virtual void update_logic(const Update_Details &ud)
  {
    return actor->update(ud);
  }
};


} // namespace Xi

#endif // end of include guard: PARTICLE_H_INCLUDED_Y6JTAFLH

