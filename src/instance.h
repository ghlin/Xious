#ifndef INSTANCE_H_INCLUDED_LDTUC52G
#define INSTANCE_H_INCLUDED_LDTUC52G

#include "config.h"
#include "object.h"

namespace Xi {

struct Static_Config
{
  uint32_t       scene_width,
                 scene_height;

  float_t        scale;
  float_t        delta_time_elpased;
};

class Instance : cc::Disable_Copy
{
  XI_PIMPL(Instance);

  Static_Config static_config;
public:
  Instance(Static_Config static_config);

  /**
   * 取得id所对应的对象.
   * \note 不存在该对象返回nullptr.
   */
  Object *query_object_by_name(const Str &id) const;

  /**
   * 取得id所对应的对象.
   * \note 不存在时返回nullptr.
   */
  Object *query_object_by_id(object_id_t id) const;

  /**
   * 注册对象.
   * \note 独占控制权.
   * \note 不采用引用计数方式管理.
   */
  object_id_t register_object(const Str &id, Ptr<Object> &&obj);


  void update(float_t dt);

  inline
  const Static_Config &get_static_config() const
  {
    return static_config;
  }
};

} // namespace Xi

#endif // end of include guard: INSTANCE_H_INCLUDED_LDTUC52G

