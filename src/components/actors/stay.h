#ifndef STAY_H_INCLUDED_MKLAHN5O
#define STAY_H_INCLUDED_MKLAHN5O

#include "common.h"

namespace Xi {

class Stay : public Actor
{
public:
  enum Exports : size_t
  {
    V_Stay_At = Component_Interface_Exports::V_First_IDX
  };

  inline void set_stay_at(vec2 stay_at)
  {
    v_slots[Exports::V_Stay_At] = stay_at;
  }

  inline vec2 get_stay_at() const
  {
    return v_slots[Exports::V_Stay_At];
  }

private:
  virtual Phy_Status do_update(const Update_Details &ud) override
};

} // namespace Xi


#endif // end of include guard: STAY_H_INCLUDED_MKLAHN5O

