#ifndef UPDATEDETAILS_H_INCLUDED_Z2AWOYEI
#define UPDATEDETAILS_H_INCLUDED_Z2AWOYEI

#include "config.h"

namespace Xi {

struct Update_Details
{
  frame_t         frame;
  frame_t         delta_frame;
  float_t         time_elpased;
  float_t         delta_time_elpased;

  Entity         *focus;
  Entity         *charactor;
  Chapter        *chapter;

  struct World_Border
  {
    float_t       width, height,
                  ws, hs; // half.
  };

  World_Border    border;
};

} // namespace Xi

#endif // end of include guard: UPDATEDETAILS_H_INCLUDED_Z2AWOYEI

