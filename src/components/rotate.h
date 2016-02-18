#ifndef ROTATE_H_INCLUDED_8WWKOUMD
#define ROTATE_H_INCLUDED_8WWKOUMD

#include "../task.h"
#include "../valueprovider.h"

namespace Xi {

class Rotate : public Task
{
  using Super = Task;
private:
  Handle<Task>           original;
  Handle<Value_Provider> angle;
public:
  inline
  const Handle<Task> &get_original() const
  {
    return original;
  }

  inline
  const Handle<Value_Provider> get_angle() const
  {
    return angle;
  }

  XI_PROP_EXPORT( (Original_Motion, original)
                , (Angle, angle)
                , (Current_Angle, angle->get_position_value(), RO)
                , (Current_Omega, angle->get_velocity_value(), RO)
                );
public:
  Rotate() { }

  Rotate(Handle<Task>           original,
         Handle<Value_Provider> angle)
    : original(std::move(original))
    , angle(std::move(angle))
  { }

  inline float_t get_current_angle() const
  {
    return angle->get_position_value();
  }

  inline float_t get_current_omega() const
  {
    return angle->get_velocity_value();
  }

  inline vec_t get_original_position() const
  {
    return original->get_position();
  }

  inline vec_t get_original_velocity() const
  {
    return original->get_velocity();
  }

protected:
  virtual void update_logic(const Update_Details &ud) override final;
};

} // namespace Xi

#endif // end of include guard: ROTATE_H_INCLUDED_8WWKOUMD

