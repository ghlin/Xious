#ifndef MOTIONXY_H_INCLUDED_CIXFP5SW
#define MOTIONXY_H_INCLUDED_CIXFP5SW

#include "../task.h"
#include "../valueprovider.h"
#include "../actors/resolution.h"

namespace Xi {

class Motion_XY : public Task
{
  using Super = Task;
protected:
  Handle<Value_Provider> x_motion;
  Handle<Value_Provider> y_motion;

  XI_PROP_EXPORT( (X_Motion, x_motion)
                , (Y_Motion, y_motion)
                );
public:
  Motion_XY()
  { }

  Motion_XY(Handle<Value_Provider> x_motion,
            Handle<Value_Provider> y_motion)
    : x_motion(x_motion)
    , y_motion(y_motion)
  { }

  Motion_XY(Handle<Value_Provider> original,
            float_t                angle)
    : x_motion(resolve_x_part(original, angle))
    , y_motion(resolve_y_part(original, angle))
  { }
protected:
  virtual void update_logic(const Update_Details &ud) override final
  {
    x_motion->update(ud);
    y_motion->update(ud);
  }
};


} // namespace Xi

#endif // end of include guard: MOTIONXY_H_INCLUDED_CIXFP5SW

