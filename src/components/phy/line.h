#ifndef LINE_H_INCLUDED_MYB5EVKW
#define LINE_H_INCLUDED_MYB5EVKW

#include "../common.h"

namespace Xi {

// todo
class Line : public Phy_Component
{
public:
  Phy_Status        end_point;
  float_t           time;

  float_t           finish_time;
  float_t           finish_distance2;

private:
  virtual Phy_Status do_update(const Update_Details &) override final;
};

} // namespace Xi





#endif // end of include guard: LINE_H_INCLUDED_MYB5EVKW

