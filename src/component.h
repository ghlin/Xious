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

namespace details {
struct key_dummy_s { };
} // namespace details

using param_key_t = const details::key_dummy_s *;

using param_type_v_t = vec2;
using param_type_x_t = Pooled_Object *;
using param_type_i_t = int32_t;
using param_type_u_t = uint32_t;
using param_type_f_t = float_t;


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

protected:
  virtual param_type_f_t   query_f(param_key_t key) const;
  virtual param_type_v_t   query_v(param_key_t key) const;
  virtual param_type_i_t   query_i(param_key_t key) const;
  virtual param_type_u_t   query_u(param_key_t key) const;
  virtual param_type_x_t  *query_x(param_key_t key) const;

  virtual void set_f(param_key_t key, param_type_f_t);
  virtual void set_v(param_key_t key, param_type_v_t);
  virtual void set_i(param_key_t key, param_type_i_t);
  virtual void set_u(param_key_t key, param_type_u_t);
  virtual void set_x(param_key_t key, param_type_x_t);
};


/**
 * 具体组件的基类
 */
template <class X>
class X_Component : public Component
{
  X            last_status = { };
  float_t      time_elpased;
  uint32_t     this_frame;
  uint32_t     last_frame;

public:
  inline uint32_t get_frame() const
  {
    return this_frame;
  }

  inline float_t get_time_elpased() const
  {
    return time_elpased;
  }

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

#define _XIC_TOUPPER(x) XI_JOIN(_XIC_UPPER_, x)
#define _XIC_UPPER_v V
#define _XIC_UPPER_x X
#define _XIC_UPPER_i I
#define _XIC_UPPER_u U
#define _XIC_UPPER_f F
#define _XIC_TYPE(suffix) XI_JOIN(param_type_, suffix, _t)

#define _XIC_PARAM(suffix, name) \
private: \
  _XIC_TYPE(suffix) name; \
  const static details::key_dummy_s XI_JOIN(suffix, _key_, name); \
public: \
  inline _XIC_TYPE(suffix) XI_JOIN(get_, name)() const \
  { return name; } \
  inline void XI_JOIN(set_, name)(_XIC_TYPE(suffix) param) \
  { name = param; } \
  inline param_key_t XI_JOIN(get_, suffix, _key_, name)() const \
  { return &XI_JOIN(suffix, _key_, name); } \

#define _XIC_PARAM_v(name) _XIC_PARAM(v, name)
#define _XIC_PARAM_f(name) _XIC_PARAM(f, name)
#define _XIC_PARAM_i(name) _XIC_PARAM(i, name)
#define _XIC_PARAM_u(name) _XIC_PARAM(u, name)
#define _XIC_PARAM_x(name) _XIC_PARAM(x, name)

#define _XIC_DECLARE_INTERFACE(suffix) \
protected: \
  virtual void XI_JOIN(set_, suffix)(param_key_t, _XIC_TYPE(suffix)) override; \
  virtual _XIC_TYPE(suffix) XI_JOIN(query_, suffix)(param_key_t) const override;

#define _XIC_SETTER_BEGIN(Klass, suffix) \
  void Klass::XI_JOIN(set_, suffix)(param_key_t key, _XIC_TYPE(suffix) param) \
  {
#define _XIC_SETTER(suffix, name) \
    if (key == &XI_JOIN(suffix, _key_, name)) \
    { name = param; return; }

#define _XIC_SETTER_v(name) _XIC_SETTER(v, name)
#define _XIC_SETTER_f(name) _XIC_SETTER(f, name)
#define _XIC_SETTER_i(name) _XIC_SETTER(i, name)
#define _XIC_SETTER_u(name) _XIC_SETTER(u, name)
#define _XIC_SETTER_x(name) _XIC_SETTER(x, name)

#define _XIC_SETTER_END(suffix) \
  return Super::XI_JOIN(set_, suffix)(key, param); }

#define _XIC_GETTER_BEGIN(Klass, suffix) \
  _XIC_TYPE(suffix) Klass::XI_JOIN(query_, suffix)(param_key_t key) const \
  {
#define _XIC_GETTER(suffix, name) \
    if (key == &XI_JOIN(suffix, _key_, name)) \
      return name;

#define _XIC_GETTER_v(name) _XIC_GETTER(v, name)
#define _XIC_GETTER_f(name) _XIC_GETTER(f, name)
#define _XIC_GETTER_i(name) _XIC_GETTER(i, name)
#define _XIC_GETTER_u(name) _XIC_GETTER(u, name)
#define _XIC_GETTER_x(name) _XIC_GETTER(x, name)

#define _XIC_GETTER_END(suffix) \
    return Super::XI_JOIN(query_, suffix)(key); }

#define _XIC_COMPLETE_KEY(Klass, suffix, name) \
  const details::key_dummy_s Klass::XI_JOIN(suffix, _key_, name) = {};

#define _XIC_COMPLETE_KEY_v(name) _XIC_COMPLETE_KEY(_Klass, v, name)
#define _XIC_COMPLETE_KEY_f(name) _XIC_COMPLETE_KEY(_Klass, f, name)
#define _XIC_COMPLETE_KEY_i(name) _XIC_COMPLETE_KEY(_Klass, i, name)
#define _XIC_COMPLETE_KEY_u(name) _XIC_COMPLETE_KEY(_Klass, u, name)
#define _XIC_COMPLETE_KEY_x(name) _XIC_COMPLETE_KEY(_Klass, x, name)


#define XIC_COMPLETE(Klass, suffix, ...) \
  using _Klass = Klass; \
  XI_FOREACH(XI_JOIN(_XIC_COMPLETE_KEY_, suffix), , __VA_ARGS__) \
  _XIC_SETTER_BEGIN(Klass, suffix) \
    XI_FOREACH(XI_JOIN(_XIC_SETTER_, suffix), , __VA_ARGS__) \
  _XIC_SETTER_END(suffix) \
  _XIC_GETTER_BEGIN(Klass, suffix) \
    XI_FOREACH(XI_JOIN(_XIC_GETTER_, suffix), , __VA_ARGS__) \
  _XIC_GETTER_END(suffix) \

#define XIC_EXPORT(suffix, ...) \
  _XIC_DECLARE_INTERFACE(suffix) \
  XI_FOREACH(XI_JOIN(_XIC_PARAM_, suffix), ,__VA_ARGS__)

#endif // end of include guard: COMPONENT_H_INCLUDED_XYT97BPW

