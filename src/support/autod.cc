#include "autod.h"
#include "test.h"

namespace Xi {

XI_UNIT_TEST_SCOPE
{
  using namespace AutoD;

#define Display_Expr(expr...) \
  xprintf(stderr, "Expr         = %s\n",   #expr); \
  xprintf(stderr, "Expr.Details = %s\n",   u_pretty_typename<decltype(expr)>()); \
  xprintf(stderr, "Expr         = %s\n",   (expr).dump()); \
  xprintf(stderr, "Expr.Reduced = %s\n\n", Reduce<typename decltype(expr)::Expr>::dump(0))

  Display_Expr($3 * $2);
}


} // namespace Xi

