#ifndef UPDATEDETAILS_H_INCLUDED_E2VYDSLF
#define UPDATEDETAILS_H_INCLUDED_E2VYDSLF


#include "config.h"

namespace Xi {

using frame_t = uint64_t;

struct Phy_Status
{
  vec2       position;
  vec2       velocity;
};

struct Art_Status
{
  // TODO
};

struct Evt_Status
{
  // TODO
};

struct Dir_Status
{
  float_t  alpha;
};

struct Update_Details
{
  float_t       delta_time_elpased;
  float_t       total_time_elpased;

  float_t       frame_prograss;
  float_t       frame_rest;

  frame_t       delta_frame; ///< 应当为1
  frame_t       total_frame;

  Entity       *special;
  Entity       *self;

  Renderer     *renderer;

  Phy_Status    last_phy_status;
  Dir_Status    last_dir_status;
  Art_Status    last_art_status;
  Evt_Status    last_evt_status;
};


} // namespace Xi

#endif // end of include guard: UPDATEDETAILS_H_INCLUDED_E2VYDSLF

