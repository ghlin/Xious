#ifndef FOREACH_H_INCLUDED_TCDUPKB7
#define FOREACH_H_INCLUDED_TCDUPKB7

#include "common.h"

namespace Xi {

template < class X
         , template <class ...> class Container>
class Foreach_Component : public Container<X>
{
  using Base = Container<X>;
public:
  using Base::Base;

private:
  virtual X do_update(const Update_Details &ud) override
  {
    X last;

    for (auto &&component : *this)
      last = component->update(ud);

    return last;
  }
};

} // namespace Xi

#endif // end of include guard: FOREACH_H_INCLUDED_TCDUPKB7

