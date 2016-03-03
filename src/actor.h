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
    // TODO: Add sfinae checker 2016-03-02 22:02:32
    using Use_Before_Routine = typename Client::Use_Before_Routine;
    using Use_After_Routine  = typename Client::Use_After_Routine;

    constexpr bool once_policy =
      std::is_same< typename Client::Update_Once
                  , std::true_type>::value;

    invoke_before_routine(ud, Use_Before_Routine());

    if (!once_policy || !updated_this_frame(ud))
    {
      frame += ud.delta_frame;
      token  = ud.frame;

      time_elpased += ud.delta_time_elpased;

      static_cast<Client *>(this)->update_routine(ud);
    }

    invoke_after_routine(ud, Use_After_Routine());
  }
};

class Simple_Actor : public chain
                     < With<Actor, Simple_Actor>
                     , addin<Enable_Simple_Update_Routine>
                     >
{
public:
  virtual void update_routine(const Update_Details &ud) = 0;
};

class Controller : public chain
                   < With<Actor, Controller>
                   , addin<Enable_Stated_Update_Routine>
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

#endif // end of include guard: ACTOR_H_INCLUDED_ZTWDMRLV

