#ifndef PARAMETERIZED_H_INCLUDED_ZUOANP7S
#define PARAMETERIZED_H_INCLUDED_ZUOANP7S

#include "../motion.h"

namespace Xi {

using  Update_Function = vec_t (*)( float_t ///< time_elpased
                                  , float_t ///< duration
                                  , float_t ///< change_value
                                  );

enum After_Policy
{
  AP_Continue,
  AP_Stop,
  AP_Reset,
};

struct Update_Parameter
{
  After_Policy       after_policy;
  Update_Function    update_function;
  float_t            duration,
                     change_value;
};

class Parameterized_Motion : public Motion
{
  using Super = Motion;
protected:
  Update_Parameter upx, upy;

  XI_PROP_EXPORT( (Update_Parameter_X, upx)
                , (Update_Parameter_Y, upy)
                );
public:
  Parameterized_Motion(Update_Parameter upx,
                       Update_Parameter upy)
    : upx(upx)
    , upy(upy)
  { }
protected:
  virtual void update_logic(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: PARAMETERIZED_H_INCLUDED_ZUOANP7S
