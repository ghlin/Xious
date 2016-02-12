#ifndef COMPOSE_H_INCLUDED_G8A1O57M
#define COMPOSE_H_INCLUDED_G8A1O57M

#include "../task.h"

namespace Xi {

class Composed_Task : public Task
{
  using Super = Task;

protected:
  std::vector<Handle<Task>>     tasks;

  XI_PROP_EXPORT( (Tasks, tasks)
                , (Is_Empty, tasks.empty(), RO)
                , (First_Task, tasks.front(), RO)
                );

public:
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
  virtual void update_logic(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: COMPOSE_H_INCLUDED_G8A1O57M

