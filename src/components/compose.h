#ifndef COMPOSE_H_INCLUDED_G8A1O57M
#define COMPOSE_H_INCLUDED_G8A1O57M

#include "../task.h"

namespace Xi {

class Composed_Task : public Implements<Task, Composed_Task>
{
  std::vector<Handle<Task>>     tasks;

  XI_PROP_EXPORT( (Tasks, tasks)
                , (Is_Empty, tasks.empty(), RO)
                , (First_Task, tasks.front(), RO)
                );

public:
  Composed_Task() { }

  Composed_Task(const Composed_Task &composed_task)
    : Super(composed_task)
    , tasks(u_map(composed_task.tasks, [] (const auto &task)
                  {
                    return handle_cast<Task>(task->clone());
                  }))
  { }

  Composed_Task(Composed_Task &&) = default;

  template <class ...Args>
  Composed_Task(Args &&...args)
    : tasks(std::forward<Args>(args)...)
  { }

  inline void push_back(Handle<Task> next)
  {
    tasks.push_back(next);
  }

  virtual Handle<Prototype> clone() const override;
protected:
  virtual void update_routine(const Update_Details &ud) override;
};

template <class ...Tasks>
static inline
auto compose(Tasks &&...tasks)
{
  return make_handle<Composed_Task>(std::forward<Tasks>(tasks)...);
}

} // namespace Xi

#endif // end of include guard: COMPOSE_H_INCLUDED_G8A1O57M

