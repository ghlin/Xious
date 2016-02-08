#ifndef WINDY_H_INCLUDED_TPLE7IVU
#define WINDY_H_INCLUDED_TPLE7IVU

#include "../actor.h"

namespace Xi {


class Windy : public Actor
{
  using Super = Actor;

  virtual Phy_Status do_update(const Update_Details &ud) override;

  XIC_EXPORT(v, wind_dir);
};

} // namespace Xi



#endif // end of include guard: WINDY_H_INCLUDED_TPLE7IVU

