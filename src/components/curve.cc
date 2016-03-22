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

  auto grow_pi = [] (const Update_Details &, auto *args)
  {
    args->_0 += M_PI / 4;
  };

  auto sin_cos = make_expr_value_provider($sin($x), grow_pi);
  // sin(x)
  // cos(x)
  // -sin(x) / sin(-x)

  xprintf(stderr,
          "(%f, %f, %f) should be (%f, %f, %f)\n",
          sin_cos->get_position_value(),
          sin_cos->get_velocity_value(),
          sin_cos->get_acceleration_value(),
          std::sin(0), std::cos(0), std::sin(0));

  sin_cos->update({ });

  xprintf(stderr,
          "(%f, %f, %f) should be (%f, %f, %f)\n",
          sin_cos->get_position_value(),
          sin_cos->get_velocity_value(),
          sin_cos->get_acceleration_value(),
          std::sin(M_PI / 4), std::cos(M_PI / 4), std::sin(-M_PI / 4));
}

} // namespace Xi

