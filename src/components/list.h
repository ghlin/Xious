#ifndef LIST_H_INCLUDED_VT73HKT2
#define LIST_H_INCLUDED_VT73HKT2

#include "component.h"

namespace Xi {


struct Wait_All { static bool apply(bool r) { return r;  } };
struct Wait_Any { static bool apply(bool r) { return !r; } };

template <class Wait_Policy>
class List_Task : public Implements<With<Phased_Task, List_Task<Wait_Policy>>, addin<Obj_List>>
{
  mutable Opt<bool> cached = false;

debug_or_protect:
  using Super = typename List_Task::Super;
public:
  using Super::Super;

  List_Task(List_Task &wa) = default;

  inline void clear_cache()
  {
    cached = { };
  }

  virtual void update_routine(const Update_Details &ud) override final
  {
    bool done = Wait_Policy::apply(true);

    for (auto &&task : this->list)
    {
      task->update(ud);

      if (Wait_Policy::apply(!task->complete()))
        done = true;
    }

    cached = { done };
  }

  virtual bool complete() const override final
  {
    if (cached)
      return *cached;

    bool done = Wait_Policy::apply(true);

    for (auto &&task : this->list)
    {
      if (Wait_Policy::apply(!task->complete()))
      {
        done = true;
        break;
      }
    }

    cached = { done };

    return done;
  }

  virtual void rewind() override final
  {
    cached = { false };

    for (auto &&task : this->list)
      task->rewind();
  }

  XI_PROP_EXPORT( (Cached, static_cast<bool>(cached), RO)
                , (Policy, Wait_Policy::apply(true),  RO)
                );
};

using Wait_All_List = List_Task<Wait_All>;
using Wait_Any_List = List_Task<Wait_Any>;

} // namespace Xi

#endif // end of include guard: LIST_H_INCLUDED_VT73HKT2

