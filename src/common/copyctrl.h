#ifndef COPYCTRL_H_INCLUDED_DHKQG5V8
#define COPYCTRL_H_INCLUDED_DHKQG5V8

namespace Xi {
namespace cc {

struct Disable_Copy_Assignment
{
  Disable_Copy_Assignment() = default;
  Disable_Copy_Assignment &operator =(const Disable_Copy_Assignment &) = delete;
};

struct Disable_Copy_Construct
{
  Disable_Copy_Construct() = default;
  Disable_Copy_Construct(const Disable_Copy_Construct &) = delete;
};

struct Disable_Copy
  : Disable_Copy_Assignment
  , Disable_Copy_Construct
{
  Disable_Copy() = default;
};



struct Disable_Move_Assignment
{
  Disable_Move_Assignment() = default;
  Disable_Move_Assignment &operator =(Disable_Move_Assignment &&) = delete;
};

struct Disable_Move_Construct
{
  Disable_Move_Construct() = default;
  Disable_Move_Construct(Disable_Move_Construct &&) = delete;
};

struct Disable_Move
  : Disable_Move_Assignment
  , Disable_Move_Construct
{
  Disable_Move() = default;
};

} // namespace cc
} // namespace Xi



#endif // end of include guard: COPYCTRL_H_INCLUDED_DHKQG5V8

