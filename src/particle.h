#ifndef PARTICLE_H_INCLUDED_Y6JTAFLH
#define PARTICLE_H_INCLUDED_Y6JTAFLH

#include "task.h"

namespace Xi {

class Particle : public Actor
{
  using Super = Actor;
protected:

  XI_PROP_EXPORT( (Task, task)
                , (Flags, flags)
                , (Tag, tag)
                );
public:
  Handle<Task>        task;
  uint32_t            flags = 0,
                      tag   = 0;

  Particle() { }
  Particle(const Particle &) = default;
  Particle(Particle &&) = default;

  Particle(Handle<Task>   task,
           uint32_t       flags,
           uint32_t       tag)
    : task(std::move(task))
    , flags(flags)
    , tag(tag)
  { }


  inline vec_t get_position() const
  {
    return task->get_position();
  }

  inline vec_t get_velocity() const
  {
    return task->get_velocity();
  }

protected:
  virtual void update_logic(const Update_Details &ud) override
  {
    return task->update(ud);
  }
};


} // namespace Xi

#endif // end of include guard: PARTICLE_H_INCLUDED_Y6JTAFLH

