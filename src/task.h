#ifndef TASK_H_INCLUDED_5KI9LKLH
#define TASK_H_INCLUDED_5KI9LKLH

#include "actor.h"
#include "util/math.h"

namespace Xi {

class Task : public Extends<Actor>
{
public:
  virtual bool complete() const; /* default: aways false */
  virtual void rewind() = 0;
  virtual bool can_rewind() const; /* default: aways false */
public:
  XI_PROP_EXPORT( (Complete, complete(), RO)
                , (Can_Rewind, can_rewind(), RO));
};

class Simple_Task : public chain
                    < With<Task, Simple_Task>
                    , addin<Enable_Simple_Update_Routine>
                    >
{
public:
  virtual void update_routine(const Update_Details &ud) = 0;
};

class Phased_Task : public chain
                    < With<Task, Phased_Task>
                    , addin<Enable_Stated_Update_Routine>
                    >
{
public:
  virtual void update_routine(const Update_Details &ud) = 0;

  virtual void before_update_routine(const Update_Details &ud);
  virtual void after_update_routine(const Update_Details &ud);

  using update_once = std::true_type;
};


} // namespace Xi

#endif // end of include guard: TASK_H_INCLUDED_5KI9LKLH

