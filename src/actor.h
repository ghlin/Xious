#ifndef ACTOR_H_INCLUDED_ZTWDMRLV
#define ACTOR_H_INCLUDED_ZTWDMRLV

#include "object.h"
#include "updatedetails.h"

namespace Xi {

class Actor : public Extends<Prototype>
{
public:
  virtual void update(const Update_Details &ud) = 0;
};

template <class S, class With>
class Enable_Simple_Update_Routine : public S
{
protected:
  float_t        time_elpased = 0.0f;

  using Super = S;
public:
  using Super::Super;

  Enable_Simple_Update_Routine() { }

  Enable_Simple_Update_Routine(const Enable_Simple_Update_Routine &r)
    : Super(r)
  { }

  Enable_Simple_Update_Routine(Enable_Simple_Update_Routine &&r)
    : Super(std::move(r))
  { }

  inline float_t get_time_elpased() const
  {
    return time_elpased;
  }

  virtual void update(const Update_Details &ud) override final
  {
    time_elpased += ud.delta_time_elpased;

    static_cast<typename With::Client *>(this)->update_routine(ud);
  }

  XI_PROP_EXPORT((Time_Elpased, time_elpased));
};

XI_GENERATE_MEMBER_DETECTOR(before_update_routine);
XI_GENERATE_MEMBER_DETECTOR(after_update_routine);

XI_GENERATE_TYPEDEF_DETECTOR(update_once);

template <class S, class With>
class Enable_Stated_Update_Routine : public S
{
protected:
  using Super = S;
public:
  using Super::Super;
protected:
  float_t       time_elpased = 0;
  frame_t       token = std::numeric_limits<frame_t>::max(),
                frame = 0;
public:
  Enable_Stated_Update_Routine(const Enable_Stated_Update_Routine &r)
    : Super(r)
  { }

  Enable_Stated_Update_Routine(Enable_Stated_Update_Routine &&r)
    : Super(std::move(r))
  { }

  Enable_Stated_Update_Routine()
    : Super()
  { }

  XI_PROP_EXPORT( (Time_Elpased, time_elpased)
                , (Frame, frame));
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
    return token == ud.frame;
  }

private:
  using Client = typename With::Client;

  void invoke_before_routine(const Update_Details &ud, const std::true_type &/* yes */)
  {
    static_cast<Client *>(this)->before_update_routine(ud);
  }

  void invoke_before_routine(const Update_Details &, const std::false_type &/* no */)
  {
    /* do nothing. */
  }

  void invoke_after_routine(const Update_Details &ud, const std::true_type &/* yes */)
  {
    static_cast<Client *>(this)->after_update_routine(ud);
  }

  void invoke_after_routine(const Update_Details &, const std::false_type &/* no */)
  {
    /* do nothing. */
  }
public:
  virtual void update(const Update_Details &ud) override final
  {

    using has_before_update_routine = details::has_member_before_update_routine_checker<Client>;
    using has_after_update_routine  = details::has_member_after_update_routine_checker<Client>;
    using update_once               = details::has_typedef_update_once_checker<Client>;

    invoke_before_routine(ud, has_before_update_routine());

    if (!update_once::value || !updated_this_frame(ud))
    {
      frame += ud.delta_frame;
      token  = ud.frame;

      time_elpased += ud.delta_time_elpased;

      static_cast<Client *>(this)->update_routine(ud);
    }

    invoke_after_routine(ud, has_after_update_routine());
  }
};


} // namespace Xi

#endif // end of include guard: ACTOR_H_INCLUDED_ZTWDMRLV

