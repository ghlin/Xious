#ifndef UPDATEDETAILS_H_INCLUDED_Z2AWOYEI
#define UPDATEDETAILS_H_INCLUDED_Z2AWOYEI

#include "config.h"

namespace Xi {

struct Update_Details
{
  Instance       *instance;
  frame_t         frame;
  frame_t         delta_frame;
  float_t         time_elpased;
  float_t         delta_time_elpased;

  Entity         *focus;
  Entity         *charactor;
  Chapter        *chapter;
};

} // namespace Xi

#endif // end of include guard: UPDATEDETAILS_H_INCLUDED_Z2AWOYEI

