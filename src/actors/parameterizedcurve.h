#ifndef PARAMETERIZEDCURVE_H_INCLUDED_NLHOAIF2
#define PARAMETERIZEDCURVE_H_INCLUDED_NLHOAIF2

#include "../valueprovider.h"

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

struct Update_Parameter
{
  Update_Complete_Policy update_complete_policy;
  Update_Function        update_function;
  float_t                duration,
                         change_value;
};

class Parameterized_Curve : public Value_Provider
{
  using Super = Value_Provider;
protected:
  Update_Parameter update_parameter;
  float_t          update_time_elpased;
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
  Parameterized_Curve(Update_Parameter update_parameter,
                       float_t         start_time = 0.0f)
    : update_parameter(update_parameter)
    , update_time_elpased(start_time)
  { }


  virtual float_t get_position_value() const override final
  {
    return position_value;
  }

  virtual float_t get_velocity_value() const override final
  {
    return velocity_value;
  }
protected:
  virtual void update_logic(const Update_Details &ud) override;
public:
  XI_COPY_CLONE(Parameterized_Curve)
};

} // namespace Xi

#endif // end of include guard: PARAMETERIZEDCURVE_H_INCLUDED_NLHOAIF2

