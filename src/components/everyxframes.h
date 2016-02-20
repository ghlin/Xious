#ifndef EVERYXFRAMES_H_INCLUDED_WQKP3N0I
#define EVERYXFRAMES_H_INCLUDED_WQKP3N0I

#include "../task.h"

namespace Xi {

template <class Upd_Object>
class Every_X_Frames : public Implements<Upd_Object, Every_X_Frames<Upd_Object>>
{
protected:
  Handle<Upd_Object>      action;

  frame_t                 x_frames;
  frame_t                 passed_frames = 0;
public:

  template <class Action>
  Every_X_Frames(Action  &&action, frame_t   x_frames)
    : action(std::forward<Action>(action))
    , x_frames(x_frames)
  { }

  inline frame_t get_x_frames() const
  {
    return x_frames;
  }

  inline const Handle<Upd_Object> &get_action() const
  {
    return action;
  }
protected:
  void update_logic(const Update_Details &ud) override final
  {
    if (++passed_frames == x_frames)
    {
      passed_frames = 0;

      action->update(ud);
    }
  }
};

using Every_X_Frames_Task = Every_X_Frames<Task>;

static inline
Handle<Task> every_x_frames(Handle<Task> task, frame_t x)
{
  return make_handle<Every_X_Frames_Task>(std::move(task), x);
}

} // namespace Xi

#endif // end of include guard: EVERYXFRAMES_H_INCLUDED_WQKP3N0I

