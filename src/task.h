#ifndef TASK_H_INCLUDED_5KI9LKLH
#define TASK_H_INCLUDED_5KI9LKLH

#include "actor.h"
#include "util/math.h"

namespace Xi {

class Task : public Extends<Actor>
{
public:
  virtual bool complete() const;   /* default: aways false */
  virtual void rewind();           /* default: do nothing */
  virtual bool can_rewind() const; /* default: aways false */
public:
  XI_PROP_EXPORT( (Complete, complete(), RO)
                , (Can_Rewind, can_rewind(), RO));
};

template <class S, class With>
class Enable_Can_Rewind : public S
{
protected:
  using Super = S;
public:
  using Super::Super;

  virtual bool can_rewind() const override final
  {
    return true;
  }
};

template <class S, class With>
class Enable_Rewind_Via_Clone : public Enable_Can_Rewind<S, With>
{
protected:
  using Super = S;
public:
  using Super::Super;

  virtual void rewind() override
  {
    auto *d_this = static_cast<typename With::Client *>(this);
    auto  d_copy = d_this->clone();

    Xi_runtime_check(d_copy.get() != d_this);

    // XXX: 2016-03-04 21:57:19
    u_reconstruct(d_this, *d_copy.get());
  }
};

template <class S, class With>
class Enable_Rewind_By_Member_Name : public Enable_Can_Rewind<S, With>
{
protected:
  using Super = S;
  using Enable_Rewind_By_Member_Name_Access = Enable_Rewind_By_Member_Name;
public:
  using Super::Super;

  virtual void rewind() override
  {
    // XXX: public? friend this? 2016-03-05 09:43:43
    static_cast<typename With::Client *>(this)->r = { };
    Super::rewind();
  }
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

