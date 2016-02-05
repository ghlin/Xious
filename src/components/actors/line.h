#ifndef LINE_H_INCLUDED_RHMNPLOW
#define LINE_H_INCLUDED_RHMNPLOW

#include "common.h"

namespace Xi {

class Line : public Actor
{
public:
  enum Exports : size_t
  {
    V_End_Point = Component_Interface_Exports::V_First_IDX,
    F_Duration  = Component_Interface_Exports::F_First_IDX,
  };

  inline void set_end_point(vec2 end_point)
  {
    v_slots[Exports::V_End_Point] = end_point;
  }

  inline vec2 get_end_point() const
  {
    return v_slots(Exports::V_End_Point);
  }

  inline void set_duration(float_t duration)
  {
    f_slots[Exports::F_Duration] = duration;
  }

  inline float_t get_duration() const
  {
    return f_slots[Exports::F_Duration];
  }
private:
  virtual Phy_Status do_update(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: LINE_H_INCLUDED_RHMNPLOW

