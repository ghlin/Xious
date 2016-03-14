#ifndef CONFIG_H_INCLUDED_YRWXK8F1
#define CONFIG_H_INCLUDED_YRWXK8F1

#include "common/pp.h"
#include "common/base.h"
#include "common/ifdebug.h"
#include "common/copyctrl.h"
#include "fwd.h"

#include <glm/glm.hpp>

namespace Xi {

using tick_t  = uint32_t;  ///< 滴答.
using frame_t = uint32_t;  ///< 帧id.

// XXX: std::float_t??? 2016-03-05 08:37:24
using float_t = float;     ///< 统一浮点类型.
using vec_t   = glm::vec2; ///< 2D向量.

template <class ...T>
using Handle = Arc<T...>; // 考虑可能改变智能指针

template <class T, class Y>
static inline
Handle<T> handle_cast(Y &&y)
{
  return std::static_pointer_cast<T>(std::forward<Y>(y));
}

template <class T, class ...Args>
static inline
Handle<T> make_handle(Args &&...args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace Xi


#endif // end of include guard: CONFIG_H_INCLUDED_YRWXK8F1

