#include "scheduler.h"

namespace Xi {


static inline
bool timed_out(const Scheduled_Task *task,
               float_t               running_time)
{
  if (u_check_bit(task->get_schedule_policy(), task->SP_Patient))
    return task->is_complete() && running_time > task->get_time_out();
  else
    return task->is_complete() || running_time > task->get_time_out();
}

static inline
bool need_accumulate(const Scheduled_Task *task)
{
  return u_check_bit(task->get_schedule_policy(), task->SP_Accumulate);
}

void Scheduler::update_logic(const Update_Details &ud)
{
  position = { };
  velocity = { };

  for (size_t i = 0; i != current_task; ++i)
  {
    auto *task = tasks.at(i).get();

    if (need_accumulate(task))
    {
      position += task->position;
      velocity += task->velocity;
    }
  }

  size_t next = current_task;

  while (timed_out(tasks[next].get(), running_time))
  {
    if (need_accumulate(tasks[next].get()))
    {
      position += tasks[next]->get_position();
      velocity += tasks[next]->get_velocity();
    }

    next         = (next + 1) % tasks.size();
    running_time = 0.0f;

    if (next == current_task)   // 执行此判断前, next已经更新过.
      Xi_die("Bad schedule.");  // 如果更新过后又回到了current_task, 说明循环了.
  }

  running_time += ud.delta_time_elpased;
  current_task  = next;

  tasks[current_task]->update(ud);

  // XXX(ghlin) : dirty... 2016-02-14 21:55:05
  if (need_accumulate(tasks[current_task].get()))
  {
    position += tasks[current_task]->get_position();
    velocity += tasks[current_task]->get_velocity();
  }
}

} // namespace Xi

