#include "demo.h"
#include "sdlutils.h"
#include "gameloop.h"
#include "textures.h"
#include "updategroup.h"
#include "player.h"

int main(int argc, const char **argv)
{
  using namespace Xi;

  init::bootstrap_initialize(argc, argv);

  SDL_Scope scope;

  unsigned long long ticks              = 0;
  auto               last_update_time   = std::chrono::high_resolution_clock::now();
  auto               very_beginning     = last_update_time;
  auto               CONFIG_FPS         = 60;
  float_t            fps_delta_time     = 1.0f / CONFIG_FPS;
  float_t            max_update_time    = 0.0f;
  float_t            max_render_time    = 0.0f;
  float_t            total_update_time  = 0.0f;
  float_t            total_render_time  = 0.0f;
  float_t            total_elpased_time = 0.0f;
  float_t            play_speed         = 1.0f;
  float_t            move_speed         = 150.0f;
  int                chapter_idx        = 0;

  auto              *renderer           = scope.renderer;
  auto              *window             = scope.window;



  ::SDL_Rect   scene_rect = { G_SCENE_X, G_SCENE_Y, G_SCENE_W, G_SCENE_H };
  ::SDL_Event  e;

  auto game_loop = Game_Loop(renderer);
  Player *player = game_loop.player.get();

  do
  {
    auto before_update                = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> diff = before_update - last_update_time;

    if (diff.count() >= fps_delta_time - 0.001f)
    {
      ++ticks;

      ::SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      ::SDL_RenderClear(renderer);

      auto before_update = std::chrono::high_resolution_clock::now();
      game_loop.update(diff.count() * play_speed);
      auto after_update = std::chrono::high_resolution_clock::now();

      auto update_time = std::chrono::duration<float>(after_update - before_update).count();
      game_loop.render();
      auto after_render = std::chrono::high_resolution_clock::now();

      auto render_time = std::chrono::duration<float>(after_render - after_update).count();

      auto total_time  = std::chrono::duration<float>(after_render - very_beginning).count();

      total_update_time += update_time;
      total_render_time += render_time;

      ::SDL_SetRenderDrawColor(renderer, 122, 122, 122, 0);
      ::SDL_RenderDrawRect(renderer, &scene_rect);

      if (update_time > max_update_time)
        max_update_time = update_time;

      if (render_time > max_render_time)
        max_render_time = render_time;

      char diag[400];
      std::sprintf(diag,
                   "[%s] (of %zu)\n"
                   "ply speed : %6f.\n"
                   "mov speed : %6f.\n"
                   "elpased   : %6f.\n"
                   "avg elp   : %6f.\n"
                   "update    : %6f.\n"
                   "max upd   : %6f.\n"
                   "render    : %6f.\n"
                   "max rnd   : %6f.\n"
                   "total     : %6f.\n"
                   "total upd : %6f.\n"
                   "total rnd : %6f.\n"
                   "avg upd   : %6f.\n"
                   "avg rnd   : %6f.\n"
                   "ticks     : %llu.\n"
                   "FPS       : %6f.\n"
                   "objs      : %zu.\n",
                   game_loop.chapter->title.c_str(),
                   get_chapters().size(),
                   play_speed,
                   move_speed,
                   diff.count(),
                   (total_elpased_time += diff.count()) / ticks,
                   update_time,
                   max_update_time,
                   render_time,
                   max_render_time,
                   total_time,
                   total_update_time,
                   total_render_time,
                   total_update_time / ticks,
                   total_render_time / ticks,
                   ticks,
                   ticks / total_time,
                   game_loop.group->entities_count());

      render_text(renderer, G_SCENE_W + 20, 10 + 10, diag);

      ::SDL_RenderPresent(renderer);

      last_update_time = std::chrono::high_resolution_clock::now();
    }

    while (::SDL_PollEvent(&e) && e.type != SDL_QUIT)
    {
      if (e.type == SDL_KEYDOWN)
      {
        Xi_log("%s key down.", ::SDL_GetKeyName(e.key.keysym.sym));
        switch (e.key.keysym.sym)
        {
        case SDLK_a: game_loop.switch_chapter(chapter_idx--); break;
        case SDLK_s: game_loop.switch_chapter(chapter_idx++); break;
        case SDLK_MINUS:  play_speed *= 2; break;
        case SDLK_EQUALS: play_speed /= 2; break;
        case SDLK_q:      move_speed  *= 1.3; break;
        case SDLK_w:      move_speed  /= 1.3; break;

        case SDLK_LEFT:   player->input = { -move_speed, 0 }; break;
        case SDLK_RIGHT:  player->input = {  move_speed, 0 }; break;
        case SDLK_UP:     player->input = { 0,  move_speed }; break;
        case SDLK_DOWN:   player->input = { 0, -move_speed }; break;
        default:
          ;
        }
      }
    }
  } while (e.type != SDL_QUIT);

  std::chrono::duration<float> total = std::chrono::high_resolution_clock::now() - very_beginning;

  Xi_log("total ticks : %llu, in %f seconds. fps(avg) ~~ %f.",
         ticks, total.count(), ticks / total.count());

  Xi_log("max update time : %f.", max_update_time);

  init::bootstrap_finalize();

  return 0;
}

