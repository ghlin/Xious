#ifndef RENDER_H_INCLUDED_FMDGCKY1
#define RENDER_H_INCLUDED_FMDGCKY1

#include "actor.h"

namespace Xi {

class Render : public Actor
{
  using Super = Actor;
public:
  virtual void draw(const Draw_Details &dd) = 0;
};

} // namespace Xi


#endif // end of include guard: RENDER_H_INCLUDED_FMDGCKY1

