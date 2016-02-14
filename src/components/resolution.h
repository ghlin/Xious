#ifndef RESOLUTION_H_INCLUDED_S5OY1T7V
#define RESOLUTION_H_INCLUDED_S5OY1T7V

#include "../valueprovider.h"

namespace Xi {

class Scaled_Value : public Value_Provider
{
  using Super = Value_Provider;
private:
  Handle<Value_Provider>  original;
  float_t                 scale_rate;

  XI_PROP_EXPORT( (Original_Value_Provider, original)
                , (Scale_Rate, scale_rate)
                );
public:
  Scaled_Value() { }

  Scaled_Value(Handle<Value_Provider> original,
               float_t                scale_rate)
    : original(original)
    , scale_rate(scale_rate)
  { }

  virtual float_t get_position_value() const override final
  {
    return original->get_position_value() * scale_rate;
  }

  virtual float_t get_velocity_value() const override final
  {
    return original->get_velocity_value() * scale_rate;
  }

  virtual float_t get_acceleration_value() const override final
  {
    return original->get_acceleration_value() * scale_rate;
  }

protected:
  virtual void update_logic(const Update_Details &ud) override final
  {
    original->update(ud);
  }
};


static inline
Handle<Value_Provider>
scale(Handle<Value_Provider> vp, float_t scale_rate)
{
  return make_handle<Scaled_Value>(vp, scale_rate);
}

static inline
Handle<Value_Provider>
resolve_x_part(Handle<Value_Provider> vp, float_t angle)
{
  auto x_scale = std::cos(angle);

  return scale(vp, x_scale);
}

static inline
Handle<Value_Provider>
resolve_y_part(Handle<Value_Provider> vp, float_t angle)
{
  auto y_scale = std::sin(angle);

  return scale(vp, y_scale);
}

static inline
std::pair< Handle<Value_Provider>
         , Handle<Value_Provider>
         >
resolve_both_part(Handle<Value_Provider> vp, float_t angle)
{
  return std::make_pair(resolve_x_part(vp, angle),
                        resolve_y_part(vp, angle));
}

} // namespace Xi

#endif // end of include guard: RESOLUTION_H_INCLUDED_S5OY1T7V

