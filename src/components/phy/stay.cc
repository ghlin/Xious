#include "stay.h"

namespace Xi {

Phy_Status Stay::do_update(const Update_Details &) override final
{
  return stay_at;
}

} // namespace Xi


