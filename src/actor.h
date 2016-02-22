#ifndef ACTOR_H_INCLUDED_ZTWDMRLV
#define ACTOR_H_INCLUDED_ZTWDMRLV

#include "object.h"
#include "updatedetails.h"

namespace Xi {

class Actor : public Extends<Prototype>
{
  float_t            time_elpased  = 0;
  frame_t            update_mark   = std::numeric_limits<frame_t>::max(),
                     frame         = 0,
                     frame_skipped = 0;
public:
  bool               skip_multiply_updating = true;

  XI_PROP_EXPORT( (Time_Elpased, time_elpased)
                , (Frame, frame)
                , (Skip_multiply_Updating, skip_multiply_updating)
                );
protected:
  virtual void update_logic(const Update_Details &ud) = 0;
public:
  Actor() { }

  Actor(const Actor &actor)
    : Actor()
    , skip_multiply_updating(another.skip_multiply_updating)
  { }

  Actor(Actor &&actor)
    : Actor()
    , skip_multiply_updating(another.skip_multiply_updating)
  { }
public:
  inline float_t get_time_elpased() const
  {
    return time_elpased;
  }

  inline frame_t get_frame() const
  {
    return frame;
  }

  inline bool updated_this_frame(const Update_Details &ud) const
  {
    return update_mark == ud.frame;
  }

  inline void update(const Update_Details &ud)
  {
    if (skip_multiply_updating && updated_this_frame(ud))
      return;

    frame         += ud.delta_frame;
    time_elpased  += ud.delta_time_elpased;

    frame_skipped  = update_mark == std::numeric_limits<frame_t>::max()
      ?              0
      :              ud.frame - update_mark - 1;

    update_mark    = ud.frame;

    update_logic(ud);
  }

  // TODO: restart/rewind method? 2016-02-22 17:20:02
};

} // namespace Xi

#endif // end of include guard: ACTOR_H_INCLUDED_ZTWDMRLV

