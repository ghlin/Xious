#ifndef DRAWDETAILS_H_INCLUDED_O1RUHRJP
#define DRAWDETAILS_H_INCLUDED_O1RUHRJP

#include "config.h"
#include "updatedetails.h"

namespace Xi {


struct Draw_Details : Update_Details
{
  // TODO(ghlin) : 2016-02-12 16:34:33
  void *renderer;

  int32_t    scene_w,
             scene_h;
};

} // namespace Xi

#endif // end of include guard: DRAWDETAILS_H_INCLUDED_O1RUHRJP

