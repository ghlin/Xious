#ifndef COMPONENT_H_INCLUDED_XYT97BPW
#define COMPONENT_H_INCLUDED_XYT97BPW

#include "config.h"
#include "object.h"
#include "updatedetails.h"

#include "phystatus.h"
#include "collistatus.h"
#include "dirstatus.h"
#include "renderstatus.h"
#include "eventstatus.h"

namespace Xi {

class Component_Update_Ctrl;



/**
 * 组件的基类. 绑定到实体上, 为实体提供状态信息.
 */
class Component : public Ref_Counted_Object
{
  /**
   * 控制更新
   */
  friend class Component_Update_Ctrl;

protected:
  float_t time_elpased = 0.0f;        ///< 组件初始化到现在流逝的时间
  frame_t last_frame   = 0;           ///< 上一帧的id
  frame_t frame        = UINT64_MAX;  ///< 当前帧的id

public:
  inline frame_t get_frame() const
  {
    return frame;
  }

  inline float_t get_time_elpased() const
  {
    return time_elpased;
  }
};



/**
 * 具体组件的基类
 */
template <class X>
class X_Component : public Component
{
  X       last_status = { };
public:
  inline X status() const
  {
    return last_status;
  }

  /**
   * 执行具体的更新动作. `last_frame == frame' 表示这一帧已经执行过更新动作
   */
  inline X update(const Update_Details &ud)
  {
    if (last_frame != frame)
    {
      time_elpased += ud.delta_time_elpased;
      frame        += ud.delta_frame;

      last_status = do_update(ud);
      last_frame  = frame;
    }

    return status();
  }

  /**
   * 此动作是否结束.
   */
  virtual bool finished() const { return false; }
private:
  /**
   * 实际更新动作.
   */
  virtual X do_update(const Update_Details &ud) = 0;
};


using Phy_Component    = X_Component<Phy_Status>;
using Colli_Component  = X_Component<Colli_Status>;
using Dir_Component    = X_Component<Dir_Status>;
using Render_Component = X_Component<Render_Staus>;
using Event_Component  = X_Component<Event_Status>;

} // namespace Xi


#endif // end of include guard: COMPONENT_H_INCLUDED_XYT97BPW

