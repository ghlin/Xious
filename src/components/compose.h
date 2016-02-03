#ifndef COMPOSE_H_INCLUDED_0PR7ZE6V
#define COMPOSE_H_INCLUDED_0PR7ZE6V

#include "common.h"

namespace Xi {

template < class X
         , template <class ...> class Container>
class Composed_Component : public Container<X>
{
  using Base = Container<X>;
public:
  using Base::Base;

  virtual bool finished() const
  {
    for (auto &&component : *this)
    {
      if (!component->finished())
        return false;
    }

    return true;
  }

private:
  virtual X do_update(const Update_Details &ud) override
  {
    X composed_status = { };

    for (auto &&component : *this)
    {
      if (!component->finished())
        composed_status += component->update(ud);
    }

    return composed_status;
  }
};

} // namespace Xi

#endif // end of include guard: COMPOSE_H_INCLUDED_0PR7ZE6V

