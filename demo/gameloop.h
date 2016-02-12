#ifndef GAMELOOP_H_INCLUDED_JSY45G0R
#define GAMELOOP_H_INCLUDED_JSY45G0R

#include "demo.h"
#include "chapter.h"


namespace Xi {

class Game_Loop : public Object
{
  using Super = Object;
public:
  Game_Loop(::SDL_Renderer *renderer);

  Draw_Details dd = { };

  Handle<Update_Group> group;

  Handle<Chapter> chapter;

  inline void change_chapter(Handle<Chapter> chapter)
  {
    this->chapter = chapter;
    this->chapter->initialize_chapter(this);

    dd.chapter    = chapter.get();

    Xi_log("set chapter %s", chapter->title);
  }

  void update(float_t delta_time_elpased);
  void render();
};



} // namespace Xi

#endif // end of include guard: GAMELOOP_H_INCLUDED_JSY45G0R

