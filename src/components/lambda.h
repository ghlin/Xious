#ifndef LAMBDA_H_INCLUDED_MJDNBIOP
#define LAMBDA_H_INCLUDED_MJDNBIOP

#include "component.h"

namespace Xi {

namespace details {

template <class Lambda>
class Lambda_Task : public Implements<With<Phased_Task, Lambda_Task<Lambda>>, addin<Enable_Can_Rewind>>
{
  Lambda lambda;

  bool   done = false;
public:
  Lambda_Task(Lambda &&lambda)
    : lambda(std::move(lambda))
  { }

  virtual void update_routine(const Update_Details &ud) override final
  {
    done = lambda(ud);
  }

  virtual bool complete() const override final
  {
    return done;
  }

  virtual void rewind() override final
  {
    done = false;
  }
};

} // namespace details

template <class Lambda>
static inline auto lambda(Lambda &&l)
{
  return make_handle<details::Lambda_Task<std::decay_t<Lambda>>>(std::forward<Lambda>(l));
}

} // namespace Xi


#endif // end of include guard: LAMBDA_H_INCLUDED_MJDNBIOP

