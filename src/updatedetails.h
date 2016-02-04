#ifndef UPDATEDETAILS_H_INCLUDED_E2VYDSLF
#define UPDATEDETAILS_H_INCLUDED_E2VYDSLF

#include "config.h"

namespace Xi {

struct Update_Details
{
  enum Special_ID : size_t
  {
    Max_Specials = 16,
    Max_Players  = 4,
    Max_Bosses   = 4,
  };

  union
  {
    Entity       *special[Max_Specials]; ///< 特化情况.

    struct                               ///< 一般情况.
    {
      Entity     *self;
      Entity     *players[Max_Players];
      Entity     *bosses[Max_Bosses];
    };
  };

  float_t       delta_time_elpased; ///< 上一帧到这一帧流逝的时间, 首帧更新时, 其值是 1 / FPS
  float_t       total_time_elpased; ///< 整个实例动作更新循环起到现在流逝的时间.

  float_t       frame_prograss;     ///< 当前进度.   \note 可能为NAN, 表示进度未知.
  float_t       frame_rest;         ///< 剩余的帧数. \note 可能为NAN, 表示剩余帧数未知.

  frame_t       delta_frame; ///< 应当为1.
  frame_t       total_frame; ///< 总共更新了的帧数.

  Renderer     *renderer;    ///< 渲染器.
};



} // namespace Xi

#endif // end of include guard: UPDATEDETAILS_H_INCLUDED_E2VYDSLF

