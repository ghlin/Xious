#ifndef AUTOD_H_INCLUDED_LPSGXT53
#define AUTOD_H_INCLUDED_LPSGXT53

#include "../config.h"

namespace Xi {
namespace AutoD {

using Integer = long long;
using Mask    = uint64_t;

struct Nil;

template <class L_, class R_>
struct Binary_Field
{
  using L = L_;
  using R = R_;
  using U = Nil;
};

template <class U_>
struct Unary_Field
{
  using U = U_;
  using L = Nil;
  using R = Nil;
};

template <Mask mask, class F_>
struct Meta_Info
{
  constexpr static Mask M = mask;
  using F = F_;
};

constexpr Mask make_mask(Mask bit)
{
  return Mask(1) << bit;
}

constexpr static Mask M_CONSTANT = make_mask(1);
constexpr static Mask M_UNARY    = make_mask(2);
constexpr static Mask M_BINARY   = make_mask(3);
constexpr static Mask M_TERM     = make_mask(4);
constexpr static Mask M_EXPR     = make_mask(5);

constexpr bool _check_mask(Mask mask,
                           Mask bit)
{
  return (mask & bit) == bit;
}

template <class T>
constexpr bool check_mask(Mask bit)
{
  return _check_mask(T::MI::M, bit);
}

template <class T, bool = std::is_same<T, typename T::Simpilified>::value>
struct Do_Reduce
{
  using Result = typename Do_Reduce<typename T::Simpilified>::Result;
};

template <class T>
struct Do_Reduce<T, true>
{
  using Result = T;
};

template <class T>
using Reduce = typename Do_Reduce<T>::Result;

#define args  attr_unused double $0 = 0, attr_unused double $1 = 0, attr_unused double $2 = 0 \
            , attr_unused double $3 = 0, attr_unused double $4 = 0, attr_unused double $5 = 0 \
            , attr_unused double $6 = 0, attr_unused double $7 = 0, attr_unused double $8 = 0 \
            , attr_unused double $9 = 0

#define $args $0, $1, $2, $3, $4, $5, $6, $7, $8, $9

constexpr attr_unused size_t _x = 0;
constexpr attr_unused size_t _y = 1;
constexpr attr_unused size_t _z = 2;

template <Integer V>
struct Int_Value
{
  using MI = Meta_Info<M_CONSTANT | M_TERM, Int_Value>;

  constexpr static Integer Value = V;

  static double apply(args)
  {
    return static_cast<double>(V);
  }

  static Str dump(int)
  {
    return u_stringify(V);
  }

  template <Integer X>
  using Deriv = Int_Value<0>;

  using Simpilified = Int_Value;
};

using _$0 = Int_Value<0>;
using _$1 = Int_Value<1>;
using _$2 = Int_Value<2>;
using _$3 = Int_Value<3>;

template <Integer V>
using Make_Integer = Int_Value<V>;

template <Integer X>
struct Variable
{
  using MI = Meta_Info<M_TERM, Variable>;

  constexpr static Integer Idx = X;

  static double apply(args)
  {
    return std::get<X>(std::make_tuple($args));
  }

  static Str dump(int)
  {
    return Str(1, 'X' + X);
  }

  template <Integer D>
  using Deriv = Make_Integer<D == X ? 1 : 0>;

  using Simpilified = Variable;
};

using _$x = Variable<_x>;
using _$y = Variable<_y>;
using _$z = Variable<_z>;

template <Integer X>
using Make_Variable = Variable<X>;

#define _gen_template_arg(x) class x
#define _gen_function_arg(x) const x &
#define _gen_apply_arg(x)    x

#define _gen_template(...)  template <XI_FOREACH_C(_gen_template_arg, __VA_ARGS__)>
#define match(...)  _gen_template(__VA_ARGS__) static constexpr int _match()
#define with(...)   _gen_template(__VA_ARGS__)                                  \
  static auto _match_case(XI_FOREACH_C(_gen_function_arg, __VA_ARGS__))         \
    -> std::enable_if_t<_match<XI_FOREACH_C(_gen_apply_arg, __VA_ARGS__)>() ==
#define match_case(N) N,
#define yield(...)  __VA_ARGS__>

template <class L_, class R_>
struct Sum : Binary_Field<L_, R_>
{
  using MI = Meta_Info<M_BINARY | M_EXPR, Sum>;

  static double apply(args)
  {
    return L_::apply($args) + R_::apply($args);
  }

  static Str dump(int level)
  {
    if (level > 1)
      return "(" + dump(0) + ")";

    return L_::dump(0) + " + " + R_::dump(0);
  }

  match(L, R)
  {
    constexpr bool L_C = check_mask<L>(M_CONSTANT);
    constexpr bool R_C = check_mask<R>(M_CONSTANT);
    constexpr bool L_0 = std::is_same<L, _$0>::value;
    constexpr bool R_0 = std::is_same<R, _$0>::value;

    if (L_C && R_C)
      return 0;

    if (L_0) return 1;
    if (R_0) return 2;

    return -1;
  }

  // TODO: 借助tuple除去冗余代码 2016-03-21 20:31:40
  with(L, R) match_case(0)  yield(Make_Integer<L::Value + R::Value>);
  with(L, R) match_case(1)  yield(R);
  with(L, R) match_case(2)  yield(L);
  with(L, R) match_case(-1) yield(Sum<L, R>);

  using SL = Reduce<L_>;
  using SR = Reduce<R_>;

  using Simpilified = decltype(_match_case(SL(), SR()));

  template <Integer D> using LD = typename L_::template Deriv<D>;
  template <Integer D> using RD = typename R_::template Deriv<D>;

  template <Integer D>
  using Deriv = Sum<LD<D>, RD<D>>;
};

template <class L, class R>
using Make_Sum = Reduce<Sum<Reduce<L>, Reduce<R>>>;

template <class L_, class R_>
struct Sub : Binary_Field<L_, R_>
{
  using MI = Meta_Info<M_BINARY | M_EXPR, Sub>;

  static double apply(args)
  {
    return L_::apply($args) - R_::apply($args);
  }

  static Str dump(int level)
  {
    if (level > 0)
      return "(" + dump(0) + ")";

    return L_::dump(0) + " - " + R_::dump(0);
  }

  match(L, R)
  {
    constexpr bool L_C = check_mask<L>(M_CONSTANT);
    constexpr bool R_C = check_mask<R>(M_CONSTANT);
    constexpr bool L_0 = std::is_same<L, _$0>::value;
    constexpr bool R_0 = std::is_same<R, _$0>::value;

    constexpr bool EQ  = std::is_same<L, R>::value;

    if (EQ)
      return 0;

    if (L_C && R_C)
      return 1;

    if (L_0) return 2;
    if (R_0) return 3;

    return -1;
  }

  with(L, R) match_case(0)  yield(_$0);
  with(L, R) match_case(1)  yield(Make_Integer<L::Value + R::Value>);
  with(L, R) match_case(2)  yield(R);
  with(L, R) match_case(3)  yield(L);
  with(L, R) match_case(-1) yield(Sub<L, R>);

  using SL = Reduce<L_>;
  using SR = Reduce<R_>;

  using Simpilified = decltype(_match_case(SL(), SR()));

  template <Integer D> using LD = typename L_::template Deriv<D>;
  template <Integer D> using RD = typename R_::template Deriv<D>;

  template <Integer D>
  using Deriv = Sub<LD<D>, RD<D>>;
};

template <class L, class R>
using Make_Sub = Reduce<Sub<Reduce<L>, Reduce<R>>>;

template <class L_, class R_>
struct Mul : Binary_Field<L_, R_>
{
  using MI = Meta_Info<M_BINARY | M_EXPR, Mul>;

  static double apply(args)
  {
    return L_::apply($args) * R_::apply($args);
  }

  static Str dump(int level)
  {
    if (level > 1)
      return "(" + dump(1) + ")";

    return L_::dump(1) + " * " + R_::dump(1);
  }

  match(L, R)
  {
    constexpr bool L_C = check_mask<L>(M_CONSTANT);
    constexpr bool R_C = check_mask<R>(M_CONSTANT);
    constexpr bool L_0 = std::is_same<L, _$0>::value;
    constexpr bool R_0 = std::is_same<R, _$0>::value;
    constexpr bool L_1 = std::is_same<L, _$1>::value;
    constexpr bool R_1 = std::is_same<R, _$1>::value;

    if (L_C && R_C) return 1;

    if (L_0 || R_0) return 2;

    if (L_1) return 3;
    if (R_1) return 4;

    return -1;
  }

  with(L, R)  match_case(1)  yield(Make_Integer<L::Value * R::Value>);
  with(L, R)  match_case(2)  yield(_$0);
  with(L, R)  match_case(3)  yield(R);
  with(L, R)  match_case(4)  yield(L);
  with(L, R)  match_case(-1) yield(Mul<L, R>);

  using SL = Reduce<L_>;
  using SR = Reduce<R_>;

  using Simpilified = decltype(_match_case(SL(), SR()));

  template <Integer D> using LD = typename L_::template Deriv<D>;
  template <Integer D> using RD = typename R_::template Deriv<D>;

  template <Integer D>
  using Deriv = Make_Sum<Mul<L_, RD<D>>, Mul<LD<D>, R_>>;
};

template <class L, class R>
using Make_Mul = Reduce<Mul<Reduce<L>, Reduce<R>>>;

// TODO:
// support Compose<F, G0, G1, G2, ..., G9>
// 2016-03-21 20:47:25
template <class F, class G>
struct Compose
{
  using MI = Meta_Info<0, Compose>;

  static_assert (check_mask<F>(M_UNARY), "unary function F is required!");

  static double apply(args)
  {
    $0 = G::apply($args);
    return F::apply($args);
  }

  static Str dump(int level)
  {
    return "(" + F::dump(level) + " where X(...) = " + G::dump(level) + ")";
  }
};

template <class T>
struct Term
{
  using Expr = T;

  static inline double apply(args)
  {
    return Expr::apply($args);
  }

  static inline Str dump()
  {
    return Expr::dump(0);
  }

  inline double operator ()(args) const
  {
    return apply($args);
  }
};

template <class L, class R>
constexpr auto operator +(const Term<L> &, const Term<R> &)
{
  return Term<Reduce<Sum<L, R>>>();
}

template <class L, class R>
constexpr auto operator -(const Term<L> &, const Term<R> &)
{
  return Term<Reduce<Sub<L, R>>>();
}

template <class L, class R>
constexpr auto operator *(const Term<L> &, const Term<R> &)
{
  return Term<Reduce<Mul<L, R>>>();
}

template <class X, Integer D>
constexpr auto operator /(const Term<X> &, const Variable<D> &)
{
  return Term<Reduce<typename X::template Deriv<D>>>();
}

attr_unused constexpr static const Term<_$0> $0 = {};
attr_unused constexpr static const Term<_$1> $1 = {};
attr_unused constexpr static const Term<_$2> $2 = {};
attr_unused constexpr static const Term<_$3> $3 = {};

attr_unused constexpr static const Term<_$x> $x = {};
attr_unused constexpr static const Term<_$y> $y = {};
attr_unused constexpr static const Term<_$z> $z = {};

} // namespace AutoD
} // namespace Xi

#undef _gen_template_arg
#undef _gen_function_arg
#undef _gen_apply_arg
#undef _gen_template
#undef match_case
#undef with
#undef yield
#undef args
#undef $args

#endif // end of include guard: AUTOD_H_INCLUDED_LPSGXT53

