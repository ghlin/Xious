#ifndef PATTERN_H_INCLUDED_HSOTJDQB
#define PATTERN_H_INCLUDED_HSOTJDQB

#include "config.h"
#include "object.h"
#include "updatedetails.h"


namespace Xi {
class Pattern_Update_Ctrl;

class Pattern_Base : public Ref_Counted_Object
{
  friend class Pattern_Update_Ctrl;
protected:
  float_t time_elpased = 0.0f;
  frame_t last_frame   = 0;
  frame_t frame        = UINT64_MAX;
public:
  inline frame_t get_frame() const
  {
    return frame;
  }

  inline float_t get_time_elpased() const
  {
    return time_elpased;
  }
};


template <class X>
class X_Pattern : public Pattern_Base
{
  X last_status;
public:
  inline X update(const Update_Details &ud)
  {
    if (last_frame == frame)
      return status(); // already updated.

    time_elpased += ud.delta_time_elpased;
    frame        += ud.delta_frame;

    last_status = _update(ud);

    last_frame = frame;

    return last_status;
  }

  inline const X &status() const
  {
    return last_status;
  }
private:
  virtual X        _update(const Update_Details &ud) = 0;
};

class Phy_Pattern : public X_Pattern<Phy_Status> { };
class Dir_Pattern : public X_Pattern<Dir_Status> { };
class Art_Pattern : public X_Pattern<Art_Status> { };
class Evt_Pattern : public X_Pattern<Evt_Status> { };


} // namespace Xi


#endif // end of include guard: PATTERN_H_INCLUDED_HSOTJDQB

