#ifndef MOTIONXY_H_INCLUDED_CIXFP5SW
#define MOTIONXY_H_INCLUDED_CIXFP5SW

#include "../task.h"
#include "../valueprovider.h"
#include "resolution.h"


namespace Xi {

class Motion_XY : public Implements<Task, Motion_XY>
{
private:
  Handle<Value_Provider> x_motion;
  Handle<Value_Provider> y_motion;

  XI_PROP_EXPORT( (X_Motion, x_motion)
                , (Y_Motion, y_motion)
                );
public:
  inline
  const Handle<Value_Provider> &get_x_motion() const
  {
    return x_motion;
  }

  inline
  const Handle<Value_Provider> &get_y_motion() const
  {
    return y_motion;
  }
public:
  Motion_XY()
  { }

  Motion_XY(Handle<Value_Provider> x_motion,
            Handle<Value_Provider> y_motion)
    : x_motion(std::move(x_motion))
    , y_motion(std::move(y_motion))
  { }

  Motion_XY(Handle<Value_Provider> original,
            float_t                angle)
    : x_motion(resolve_x_part(original, angle))
    , y_motion(resolve_y_part(original, angle))
  { }

  Motion_XY(const Motion_XY &motion_xy)
    : x_motion(handle_cast<Value_Provider>(motion_xy.x_motion->clone()))
    , y_motion(handle_cast<Value_Provider>(motion_xy.y_motion->clone()))
  { }

  Motion_XY(Motion_XY &&) = default;

protected:
  virtual void update_logic(const Update_Details &ud) override final
  {
    x_motion->update(ud);
    y_motion->update(ud);
  }
};


} // namespace Xi

#endif // end of include guard: MOTIONXY_H_INCLUDED_CIXFP5SW

