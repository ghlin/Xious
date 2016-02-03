#ifndef CONDITIONAL_H_INCLUDED_VE0943SK
#define CONDITIONAL_H_INCLUDED_VE0943SK

#include "common.h"

namespace Xi {

template <class X>
class Conditional_Component : public Component_Proxy<X>
{
public:
  using Condition_Func = std::function<bool (const Component *)>;
private:
  Condition_Func condition;

  using Base = Component_Proxy<X>;
public:
  template <class ...Args>
  Conditional_Component(Args           &&...args,
                        Condition_Func      condition)
  : Base(std::forward<Args>(args)...)
  , condition(condition)
  { }

  virtual bool finished() const override
  {
    return this->empty() || !condition ? true
      :    condition(this->front())    ? true
      :                                  this->front()->finished();
  }

private:
  virtual X do_update(const Update_Details &ud) override
  {
    return this->front()->update(ud);
  }
};

} // namespace Xi

#endif // end of include guard: CONDITIONAL_H_INCLUDED_VE0943SK

