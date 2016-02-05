#ifndef PROPERTIES_H_INCLUDED_J7SMEV86
#define PROPERTIES_H_INCLUDED_J7SMEV86

#include "../component.h"

namespace Xi {

constexpr size_t kSlot_Size = 32;

class Properties : public Component
{
public:
  float_t           f_slot[kSlot_Size];
  Object           *x_slot[kSlot_Size];
  vec2              v_slot[kSlot_Size];
  int32_t           i_slot[kSlot_Size];
};

} // namespace Xi

#endif // end of include guard: PROPERTIES_H_INCLUDED_J7SMEV86

