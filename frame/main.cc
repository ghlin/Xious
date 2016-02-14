#include "../src/support/bootstrap.h"
#include "framedefs.h"
#include "painter.h"

#include <SDL2/SDL.h>

int main(int argc, const char **argv)
{
  Xi::init::bootstrap_initialize(argc, argv);

  ::SDL_Event    e;
  do
  {
    Xi::the_painter().clear_screen(0, 0, 0, 0);
    Xi::the_painter().draw_rect(Xi::SCENE_BOX, 255, 0, 0, 0);
    Xi::the_painter().do_render();

    ::SDL_Delay(100);

    while (::SDL_PollEvent(&e) && e.type != ::SDL_QUIT);
  } while (e.type != ::SDL_QUIT);

  Xi::init::bootstrap_finalize();

  return 0;
}

