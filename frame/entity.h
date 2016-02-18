#ifndef ENTITY_H_INCLUDED_WQU0PM9N
#define ENTITY_H_INCLUDED_WQU0PM9N

#include "../src/entity.h"

namespace Xi {

enum Entity_Type : uint32_t
{
  ET_Ghost,
  ET_Enemy_Bullet,
  ET_Enemy_Ship,
  ET_Player_Bullet,
  ET_Player_Ship,
};

enum Entity_Flags : uint32_t
{
  EF_Spawning    = 0x0001,
  EF_Dying       = 0x0002,
};

class My_Entity : public Entity
{
  using Super = Entity;

public:
  My_Entity() { }

  Entity_Type    entity_type;
  uint32_t       entity_flags;
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_WQU0PM9N

