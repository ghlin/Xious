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
class Component_Param_Ctrl;

using param_key_t = size_t;

/**
 * 组件的基类. 绑定到实体上, 为实体提供状态信息.
 */
class Component : public Pooled_Object
{
  /**
   * 控制更新
   */
  friend class Component_Update_Ctrl;
  friend class Component_Param_Ctrl;

  float_t      time_elpased;
  uint32_t     this_frame;
  uint32_t     last_frame;

private:
  virtual float_t        query_f(param_key_t key) const;
  virtual int32_t        query_i(param_key_t key) const;
  virtual uint32_t       query_u(param_key_t key) const;
  virtual uint32_t       query_u(param_key_t key) const;
  virtual Pooled_Object *query_x(param_key_t key) const;

  virtual void set_f(float_t        , param_key_t key);
  virtual void set_i(int32_t        , param_key_t key);
  virtual void set_u(uint32_t       , param_key_t key);
  virtual void set_u(uint32_t       , param_key_t key);
  virtual void set_x(Pooled_Object *, param_key_t key);

public:
  inline uint32_t get_frame() const
  {
    return this_frame;
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
  X last_status = { };
public:
  inline
  const X &get_last_status() const
  {
    return last_status;
  }

  inline
  X update(const Update_Details &ud)
  {
    if (last_frame != this_frame)
    {
      time_elpased += ud.delta_time_elpased;
      this_frame   += ud.delta_frame;

      last_status   = do_update(ud);

      last_frame    = this_frame;

      return last_status;
    }

    return do_update(ud);
  }

  inline
  bool already_updated_this_frame() const
  {
    return last_frame == this_frame;
  }

  virtual bool  finished() const = 0;
private:
  // if (already_updated_this_frame()) return last_status;
  // else xxx;
  virtual X do_update(const Update_Details &ud) = 0;
};

using Actor     = X_Component<Phy_Status>;
using Collider  = X_Component<Colli_Status>;
using Vector    = X_Component<Dir_Status>;
using Render    = X_Component<Render_Staus>;
using Commander = X_Component<Event_Status>;

} // namespace Xi


#endif // end of include guard: COMPONENT_H_INCLUDED_XYT97BPW

