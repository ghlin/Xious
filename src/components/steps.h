#ifndef STEPS_H_INCLUDED_2MBFXJXG
#define STEPS_H_INCLUDED_2MBFXJXG

#include "component.h"

namespace Xi {

// TODO: 2016-03-16 19:21:55
class Steps : public Implements
              < With<Phased_Task, Steps, Handle<Task>>
              , addin<Obj_List>
              , addin<Enable_Can_Rewind>>
{
  using Super::append;

  using Iterator = List_Type::iterator;

  Iterator current;

  inline bool reached_eol() const
  {
    return current == list.end();
  }
public:
  template <class ...T>
  Steps(T &&...t)
    : Super(std::forward<T>(t)...)
    , current(list.begin())
  { }

  Steps() = delete;

  Steps(const Steps &steps)
    : Super(List_Type(steps.list.cbegin(), steps.list.cend()))
    , current(list.begin())
  { }

  virtual bool complete() const override final
  {
    return reached_eol();
  }

  virtual void update_routine(const Update_Details &ud) override final;

  virtual void rewind() override final;
};

} // namespace Xi


#endif // end of include guard: STEPS_H_INCLUDED_2MBFXJXG

