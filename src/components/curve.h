#ifndef CURVE_H_INCLUDED_PWGZXLRF
#define CURVE_H_INCLUDED_PWGZXLRF

#include "component.h"

namespace Xi {

namespace details {

// TODO: ... 2016-03-22 14:34:44
struct Expr_Args
{
  float_t _0 = 0, _1 = 0, _2 = 0
        , _3 = 0, _4 = 0, _5 = 0
        , _6 = 0, _7 = 0, _8 = 0
        , _9 = 0;
};

template <class Expr>
class Expr_Provider : public Extends<Value_Provider>
{
protected:
  using Position_Expr     = Expr;
  using Velocity_Expr     = typename Position_Expr::template Deriv<0>;
  using Acceleration_Expr = typename Velocity_Expr::template Deriv<0>;

  Expr_Args args;
public:
  virtual float_t get_position_value()     const
  {
    return Position_Expr::apply(args._0, args._1, args._2, args._3, args._4,
                                args._5, args._6, args._7, args._8, args._9);
  }

  virtual float_t get_velocity_value()     const
  {
    return Velocity_Expr::apply(args._0, args._1, args._2, args._3, args._4,
                                args._5, args._6, args._7, args._8, args._9);
  }

  virtual float_t get_acceleration_value() const
  {
    return Acceleration_Expr::apply(args._0, args._1, args._2, args._3, args._4,
                                    args._5, args._6, args._7, args._8, args._9);
  }
};

template <class Expr, class Lambda>
class X_Expr_Provider : public Implements
                        < With<Expr_Provider<Expr>, X_Expr_Provider<Expr, Lambda>>
                        , addin<Enable_Stated_Update_Routine>
                        >
{
  Lambda lambda;
public:
  template <class X_Lambda>
  X_Expr_Provider(X_Lambda &lambda) : lambda(std::forward<X_Lambda>(lambda))
  {    }

  virtual void update_routine(const Update_Details &ud)
  {
    lambda(ud, &this->args);
  }
};

} // namespace details

template <class Term, class Lambda>
static inline auto make_expr_value_provider(const Term &,
                                            Lambda    &&lambda)
{
  using Expr = typename Term::Expr;

  return make_handle<details::X_Expr_Provider<Expr, std::decay_t<Lambda>>>(std::forward<Lambda>(lambda));
}

} // namespace Xi

#endif // end of include guard: CURVE_H_INCLUDED_PWGZXLRF

