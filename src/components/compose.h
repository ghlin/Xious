#ifndef COMPOSE_H_INCLUDED_0PR7ZE6V
#define COMPOSE_H_INCLUDED_0PR7ZE6V

#include "common.h"

namespace Xi {

template <template <class ...> class Container>
class Phy_Composer : public Container<Phy_Status>
{
  using Base = Container<Phy_Status>;
public:
  using Base::Base;

private:
  virtual Phy_Status do_update(const Update_Details &ud)
  {
    Phy_Status accu = { };

    for (auto &&component : *this)
      accu += component->update(ud);
  }
};

} // namespace Xi

#endif // end of include guard: COMPOSE_H_INCLUDED_0PR7ZE6V

