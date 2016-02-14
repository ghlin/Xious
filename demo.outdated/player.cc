#include "player.h"
#include "roundcollider.h"
#include "render.h"
#include "textures.h"

namespace Xi {

class Player_Resp : public Task
{
public:
  Player *player;

  Player_Resp(Player *player) : player(player)
  {
    position = { 0, -G_WORLD_H / 2 * 0.7 };
  }

protected:
  void update_logic(const Update_Details &ud)
  {
    auto pos = position + player->input * ud.delta_time_elpased;

    if (math::is_inside(pos, { 0, 0 }, { ud.border.ws, ud.border.hs }))
      position = pos;

    velocity = player->input;
    player->input = { };
  }
};

Player::Player()
{
  collider = std::make_shared<Round_Collider>();
  render   = std::make_shared<SDL_Render>(g_textures[TID_Player]);
  task     = std::make_shared<Player_Resp>(this);
}

} // namespace Xi

