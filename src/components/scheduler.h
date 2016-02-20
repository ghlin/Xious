#ifndef SCHEDULER_H_INCLUDED_GO1PZESN
#define SCHEDULER_H_INCLUDED_GO1PZESN

#include "../task.h"
#include "everyxframes.h"

namespace Xi {

class Scheduled_Task : public Extends<Task>
{
public:
  enum Schedule_Policy
  {
    SP_Accumulate    = 0x0,
    SP_No_Accumulate = 0x1,

    SP_Patient       = 0x0,
    SP_Eager         = 0x2,
  };
protected:
  float_t   time_out;
  uint32_t  schedule_policy;

public:

  inline uint32_t get_schedule_policy() const
  {
    return schedule_policy;
  }

  inline float_t get_time_out() const
  {
    return time_out;
  }

  virtual bool is_complete() const
  {
    return false;
  }

  XI_PROP_EXPORT( (Schedule_Policy, schedule_policy)
                , (Time_Out, time_out)
                , (Is_Complete, is_complete(), RO)
                );

public:
  Scheduled_Task() { }

  Scheduled_Task(float_t         time_out,
                 Schedule_Policy schedule_policy)
    : time_out(time_out)
    , schedule_policy(schedule_policy)
  { }
};

namespace details {

class STWrapper : public Implements<Scheduled_Task, STWrapper>
{
  Handle<Task>  task;

  XI_PROP_EXPORT((Wrapped_Task, task));
public:
  STWrapper(Handle<Task>    task,
            float_t         time_out,
            Schedule_Policy schedule_policy)
    : Base(time_out, schedule_policy)
    , task(task)
  { }

  STWrapper() { }
private:
  virtual void update_logic(const Update_Details &ud) override final
  {
    task->update(ud);
  }
};

} // namespace details


static inline
auto make_schedule(Handle<Task> task, float_t time_out, Scheduled_Task::Schedule_Policy schedule_policy)
{
  return make_handle<details::STWrapper>(std::move(task), time_out, schedule_policy);
}

class Scheduler : public Implements<Task, Scheduler>
{
  using Super = Task;
private:
  std::vector<Handle<Scheduled_Task>> tasks;
  size_t                              current_task = 0;
  float_t                             running_time = 0;

  XI_PROP_EXPORT( (Scheduled_Tasks, tasks)
                , (Current_Task_ID, current_task)
                , (Running_Time, running_time)
                );
public:
  Scheduler() { }

  template <class ...Args>
  Scheduler(Args &&...args)
    : tasks(std::forward<Args>(args)...)
    , current_task(0)
    , running_time(0)
  { }

  inline
  size_t get_current_task() const
  {
    return current_task;
  }

  inline
  const std::vector<Handle<Scheduled_Task>> &get_scheduled_tasks() const
  {
    return tasks;
  }

private:
  inline void next()
  {
    current_task = (current_task + 1) % tasks.size();
  }
protected:
  virtual void update_logic(const Update_Details &ud) override final;
};

} // namespace Xi

#endif // end of include guard: SCHEDULER_H_INCLUDED_GO1PZESN

