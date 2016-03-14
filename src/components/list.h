#ifndef LIST_H_INCLUDED_VT73HKT2
#define LIST_H_INCLUDED_VT73HKT2

#include "component.h"

namespace Xi {

class Wait_All_List : chain<With<Phased_Task, Wait_All_List, Task>, addin<Obj_List>>
{
  mutable bool            done     = false;
  mutable bool            iterated = false;
public:
  using Super::Super;

  Wait_All_List(Wait_All_List &wa) = default;

  virtual void update_routine(const Update_Details &ud) override final;
  virtual bool complete() const override final;
  virtual void rewind() override final;
};

class Wait_Any_List : chain<With<Phased_Task, Wait_Any_List, Task>, addin<Obj_List>>
{
  mutable bool            done     = false;
  mutable bool            iterated = false;
public:
  using Super::Super;

  Wait_Any_List(Wait_Any_List &wa) = default;

  virtual void update_routine(const Update_Details &ud) override final;
  virtual bool complete() const override final;
  virtual void rewind() override final;
};

} // namespace Xi

#endif // end of include guard: LIST_H_INCLUDED_VT73HKT2

