#ifndef MOTION_H_INCLUDED_XCIO5A7S
#define MOTION_H_INCLUDED_XCIO5A7S

#include "object.h"

namespace Xi {

class Motion : public Prototype
{
  using Super = Prototype;
public:
  virtual vec_t move(float_t time_elpased,
                     frame_t frame,
                     const Update_Details &ud) = 0;
};

} // namespace Xi

#endif // end of include guard: MOTION_H_INCLUDED_XCIO5A7S

