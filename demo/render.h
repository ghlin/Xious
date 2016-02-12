#ifndef RENDER_H_INCLUDED_IM7CKTHV
#define RENDER_H_INCLUDED_IM7CKTHV

#include "demo.h"

namespace Xi {

class SDL_Render : public Render
{
  using Super = Render;

  ::SDL_Texture  *texture;
public:
  SDL_Render(::SDL_Texture *texture)
    : texture(texture)
  { }

  virtual void draw(const Draw_Details &dd) override;

protected:
  virtual void update_logic(const Update_Details &ud) override;
};

} // namespace Xi

#endif // end of include guard: RENDER_H_INCLUDED_IM7CKTHV

