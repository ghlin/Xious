#ifndef PARAMETERIZEDCURVE_H_INCLUDED_NLHOAIF2
#define PARAMETERIZEDCURVE_H_INCLUDED_NLHOAIF2

#include "../valueprovider.h"
#include "../support/animationcurve.h"

namespace Xi {

using  Update_Function = vec_t (*)( float_t ///< time_elpased
                                  , float_t ///< duration
                                  , float_t ///< change_value
                                  );

/**
 * 当time_elpased超过duration时的更新策略
 */
enum Update_Complete_Policy
{
  UCP_Continue,    ///< 无视duration, 继续应用Update_Function
  UCP_Stay,        ///< 维持当前position / velocity, 不再变动
  UCP_Stop,        ///< position / velocity 置为0, 不再变动.
  UCP_Reset,       ///< 将elpased置0, 重新开始.
};

/**
 * 曲线参数.
 */
struct Update_Parameter
{
  Update_Function        update_function;
  float_t                duration,
                         change_value;
  Update_Complete_Policy update_complete_policy;
};


static inline
Update_Parameter make_update_parameter(Update_Function        update_function,
                                       float_t                duration,
                                       float_t                change_value,
                                       Update_Complete_Policy update_complete_policy)
{
  return { update_function, duration, change_value, update_complete_policy };
}

static inline
Update_Parameter make_update_parameter(curve::Curve_Type               curve_type,
                                       curve::Curve_Change_Type        curve_change_type,
                                       float_t                         duration,
                                       float_t                         change_value,
                                       Update_Complete_Policy          update_complete_policy)
{
  return make_update_parameter(curve::get_curve(curve_type, curve_change_type),
                               duration,
                               change_value,
                               update_complete_policy);
}

static inline
Update_Parameter scale(Update_Parameter up, float_t scale_rate)
{
  return make_update_parameter(up.update_function,
                               up.duration,
                               up.change_value * scale_rate,
                               up.update_complete_policy);
}

/**
 * x方向分解.
 */
static inline
Update_Parameter resolve_x_part(Update_Parameter up, float_t angle)
{
  return scale(up, std::cos(angle));
}

/**
 * y方向分解.
 */
static inline
Update_Parameter resolve_y_part(Update_Parameter up, float_t angle)
{
  return scale(up, std::sin(angle));
}


class Parameterized_Curve : public Value_Provider
{
  using Super = Value_Provider;
private:
  Update_Parameter update_parameter;
  float_t          update_time_elpased = 0;
  float_t          position_value,
                   velocity_value;

  XI_PROP_EXPORT( (Update_Parameter, update_parameter)
                , (Update_Duration, update_parameter.duration)
                , (Update_Change_Value, update_parameter.change_value)
                , (Update_Time_Elpased, update_time_elpased)
                , (Position_Value, position_value, RO)
                , (Velocity_Value, velocity_value, RO)
                );
public:
  Parameterized_Curve() { }

  Parameterized_Curve(const Parameterized_Curve &another)
    : update_parameter(another.update_parameter)
    , update_time_elpased(0)
  { }

  Parameterized_Curve(Update_Parameter update_parameter,
                      float_t          start_time = 0)
    : update_parameter(update_parameter)
    , update_time_elpased(start_time)
  { }

  inline
  const Update_Parameter &get_update_parameter() const
  {
    return update_parameter;
  }

  virtual float_t get_position_value() const override final
  {
    return position_value;
  }

  virtual float_t get_velocity_value() const override final
  {
    return velocity_value;
  }
protected:
  virtual void update_logic(const Update_Details &ud) override final;
public:
  XI_COPY_CLONE(Parameterized_Curve)
};

} // namespace Xi

#endif // end of include guard: PARAMETERIZEDCURVE_H_INCLUDED_NLHOAIF2

