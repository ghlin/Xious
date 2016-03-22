#include "curve.h"
#include "../support/test.h"
#include "../support/autod.h"

namespace Xi {


XI_UNIT_TEST_SCOPE
{
  auto grow = [] (const Update_Details &, auto *args)
  {
    args->_0 += 1;
  };

  using namespace AutoD;
  auto expr = $x + $3 * $x;

  auto value = make_expr_value_provider(expr, grow);

  xprintf(stderr,
          "(%f, %f, %f) should be (%f, %f, %f)\n",
          value->get_position_value(),
          value->get_velocity_value(),
          value->get_acceleration_value(),
          0.0f, 4.0f, 0.0f);

  value->update({ });

  xprintf(stderr,
          "(%f, %f, %f) should be (%f, %f, %f)\n",
          value->get_position_value(),
          value->get_velocity_value(),
          value->get_acceleration_value(),
          4.0f, 4.0f, 0.0f);

  xprintf(stderr,
          "%s\n%s\n%s\n",
          expr.dump(),
          (expr / _$x()).dump(),
          (expr / _$x() / _$x()).dump());
}

} // namespace Xi

