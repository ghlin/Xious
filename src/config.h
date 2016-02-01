#ifndef CONFIG_H_INCLUDED_YRWXK8F1
#define CONFIG_H_INCLUDED_YRWXK8F1

#include "common/pp.h"
#include "common/base.h"
#include "common/ifdebug.h"
#include "common/copyctrl.h"
#include "fwd.h"

#include <glm/glm.hpp>

using object_id_t = uint32_t; ///< 对象唯一id标识.
using ref_count_t = uint64_t; ///< 引用计数, 非原子类型. \note 非原子类型.

using tick_t  = uint64_t; ///< 滴答.
using frame_t = uint64_t; ///< 帧id.
using float_t = float;    ///< 统一浮点类型.
using glm::vec2;          ///< 2D向量.


#endif // end of include guard: CONFIG_H_INCLUDED_YRWXK8F1

