#ifndef CTRL_H_INCLUDED_CTGAAVT6
#define CTRL_H_INCLUDED_CTGAAVT6

#include "actor.h"

namespace Xi {

namespace addon { namespace details {

struct Keep_Time_Elpased_Info
{
  float_t        time_elpased = 0;

  Keep_Time_Elpased_Info(const Keep_Time_Elpased_Info &)
  { }

  Keep_Time_Elpased_Info(Keep_Time_Elpased_Info &&)
  { }

  inline float_t get_time_elpased() const
  {
    return time_elpased;
  }

  inline void update_time_elpased(const Update_Details &ud)
  {
    time_elpased += ud.delta_time_elpased;
  }
};

template <class B, class D>
class Simple_Update_Routine
  : public     B
  , protected  Keep_Time_Elpased_Info
{
public:
  using B::B;

  virtual void update(const Update_Details &ud) override final
  {
    this->update_time_elpased(ud);

    static_cast<D *>(this)->update_routine(ud);
  }

  XI_PROP_EXPORT((Time_Elpased, time_elpased));
};

template <class B, class D>
class Stated_Update_Routine
  : public      B
  , protected   Keep_Time_Elpased_Info
{
public:
  using B::B;

private:
  frame_t       token = std::numeric_limits<frame_t>::max(),
                frame = 0;
public:
  Stated_Update_Routine(const Stated_Update_Routine &r)
    : B(r)
  { }

  Stated_Update_Routine(Stated_Update_Routine &&r)
    : B(std::move(r))
  { }

  Stated_Update_Routine()
    : B()
  { }

  XI_PROP_EXPORT( (Time_Elpased, time_elpased)
                , (Frame, frame));

public:
  inline frame_t get_frame() const
  {
    return frame;
  }

  inline bool updated_this_frame(const Update_Details &ud) const
  {
    return token == ud.frame;
  }

private:
  void invoke_before_routine(const Update_Details &ud, const std::true_type &/* yes */)
  {
    static_cast<D *>(this)->before_update_routine(ud);
  }

  void invoke_before_routine(const Update_Details &ud, const std::false &/* no */)
  {
    /* do nothing. */
  }

  void invoke_after_routine(const Update_Details &ud, const std::true_type &/* yes */)
  {
    static_cast<D *>(this)->after_update_routine(ud);
  }

  void invoke_after_routine(const Update_Details &ud, const std::false &/* no */)
  {
    /* do nothing. */
  }
public:
  virtual void update(const Update_Details &ud) override final
  {
    // TODO: Add sfinae checker 2016-03-02 22:02:32
    using Use_Before_Routine = typename D::Use_Before_Routine;
    using Use_After_Routine  = typename D::Use_After_Routine;

    constexpr bool once_policy =
      std::is_same< typename D::Update_Once
                  , std::true_type>::value;

    invoke_before_routine(ud, Use_Before_Routine());

    if (!once_policy || !updated_this_frame(ud))
    {
      frame += ud.delta_frame;
      token  = ud.frame;

      this->update_time_elpased(ud);

      static_cast<D *>(this)->update_routine(ud);
    }

    invoke_after_routine(ud, Use_After_Routine());
  }
};

} // namespace details

using Simple_Update_Routine = Make_Addon<details::Simple_Update_Routine>;
using Stated_Update_Routine = Make_Addon<details::Stated_Update_Routine>;

} // namespace addon

class Controller : public chain
                 < With<Actor, Ctrl>
                 , Stated_Update_Routine
                 >
{
public:
  using Update_Once        = std::true_type;
  using Use_After_Routine  = std::true_type;
  using Use_Before_Routine = std::true_type;
public:
  using Super::Super;

  virtual void update_routine(const Update_Details &ud) = 0;

  // 默认为空
  virtual void before_update_routine(const Update_Details &ud);
  virtual void after_update_routine(const Update_Details &ud);
};

} // namespace Xi

#endif // end of include guard: CTRL_H_INCLUDED_CTGAAVT6

