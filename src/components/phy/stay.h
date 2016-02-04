#ifndef STAY_H_INCLUDED_73FHZODK
#define STAY_H_INCLUDED_73FHZODK

#include "../common.h"

namespace Xi {

class Stay : public Phy_Component
{
public:
  Phy_Status        stay_at;

private:
  virtual Phy_Status do_update(const Update_Details &) override final;
};


} // namespace Xi


#endif // end of include guard: STAY_H_INCLUDED_73FHZODK

