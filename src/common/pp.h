#ifndef PP_H_INCLUDED_PI681K2O
#define PP_H_INCLUDED_PI681K2O

#define XI_CAR(x, ...)     _XI_CAR(x, __VA_ARGS__)
#define _XI_CAR(x, ...)    x

#define XI_CDR(x, ...)     _XI_CDR(x, __VA_ARGS__)
#define _XI_CDR(x, ...)    __VA_ARGS__

#define XI_VAL_0       0
#define XI_VAL_PLUS_0  1
#define XI_VAL_1       1
#define XI_VAL_MINUS_1 0
#define XI_VAL_PLUS_1  2
#define XI_VAL_2       2
#define XI_VAL_MINUS_2 1
#define XI_VAL_PLUS_2  3
#define XI_VAL_3       3
#define XI_VAL_MINUS_3 2
#define XI_VAL_PLUS_3  4
#define XI_VAL_4       4
#define XI_VAL_MINUS_4 3
#define XI_VAL_PLUS_4  5
#define XI_VAL_5       5
#define XI_VAL_MINUS_5 4
#define XI_VAL_PLUS_5  6
#define XI_VAL_6       6
#define XI_VAL_MINUS_6 5
#define XI_VAL_PLUS_6  7
#define XI_VAL_7       7
#define XI_VAL_MINUS_7 6
#define XI_VAL_PLUS_7  8
#define XI_VAL_8       8
#define XI_VAL_MINUS_8 7
#define XI_VAL_PLUS_8  9
#define XI_VAL_9       9
#define XI_VAL_MINUS_9 8
#define XI_VAL_PLUS_9  10

#define XI_PLUS1(N)   XI_CAT(XI_VAL_PLUS_, N)
#define XI_MINUS1(N)  XI_CAT(XI_VAL_MINUS_, N)

#define XI_CAT(a, b)      XI_KITTY(a, b)
#define XI_KITTY(a, b)    a##b
#define XI_STRINGIFY(a)   XI_QUOTE(a)
#define XI_QUOTE(a)       #a

#define XI_NARGS_HELPER0(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, Q, ...) Q
#define XI_NARGS_HELPER(R...)       XI_NARGS_HELPER0(R)
#define XI_NARGS_DUMMY_ARGS         9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define XI_NARGS(R...)  XI_NARGS_HELPER(_, ##R, XI_NARGS_DUMMY_ARGS)

#define XI_JOIN_2(L, R)     XI_CAT(L, R)
#define XI_JOIN_3(L, R...)  XI_CAT(L, XI_JOIN_2(R))
#define XI_JOIN_4(L, R...)  XI_CAT(L, XI_JOIN_3(R))
#define XI_JOIN_5(L, R...)  XI_CAT(L, XI_JOIN_4(R))
#define XI_JOIN_6(L, R...)  XI_CAT(L, XI_JOIN_5(R))
#define XI_JOIN_7(L, R...)  XI_CAT(L, XI_JOIN_6(R))
#define XI_JOIN_8(L, R...)  XI_CAT(L, XI_JOIN_7(R))
#define XI_JOIN_9(L, R...)  XI_CAT(L, XI_JOIN_8(R))

#define XI_JOIN(R...)       XI_CAT(XI_JOIN_, XI_NARGS(R))(R)

#define XI_APPLY_0(M, F, R...)      F, ##R
#define XI_APPLY_1(M, F, R...)      M(F, ##R)
#define XI_APPLY_2(M, F, R...)      M(XI_APPLY_1(M, F, ##R), ##R)
#define XI_APPLY_3(M, F, R...)      M(XI_APPLY_2(M, F, ##R), ##R)
#define XI_APPLY_4(M, F, R...)      M(XI_APPLY_3(M, F, ##R), ##R)
#define XI_APPLY_5(M, F, R...)      M(XI_APPLY_4(M, F, ##R), ##R)
#define XI_APPLY_6(M, F, R...)      M(XI_APPLY_5(M, F, ##R), ##R)
#define XI_APPLY_7(M, F, R...)      M(XI_APPLY_6(M, F, ##R), ##R)
#define XI_APPLY_8(M, F, R...)      M(XI_APPLY_7(M, F, ##R), ##R)
#define XI_APPLY_9(M, F, R...)      M(XI_APPLY_8(M, F, ##R), ##R)

#define XI_APPLY(N, M, F, R...)     XI_CAT(XI_APPLY_, N)(M, F, ##R)

#define XI_PLUSX(N, PLS)    XI_APPLY(PLS, XI_PLUS1, N)
#define XI_MINUSX(N, MNS)   XI_APPLY(MNS, XI_MINUS1, N)

#define XI_FOREACH_1(M, C, A)                 M(A)
#define XI_FOREACH_2(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)
#define XI_FOREACH_3(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)
#define XI_FOREACH_4(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)
#define XI_FOREACH_5(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)
#define XI_FOREACH_6(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)
#define XI_FOREACH_7(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)
#define XI_FOREACH_8(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)
#define XI_FOREACH_9(M, C, A, R...)           M(A) C XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)

#define XI_FOREACH(M, C, R...)                XI_CAT(XI_FOREACH_, XI_NARGS(R))(M, C, ##R)

#define XI_COMMA                              ,

#define XI_FOREACH_C_1(M, A)                  M(A)
#define XI_FOREACH_C_2(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)
#define XI_FOREACH_C_3(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)
#define XI_FOREACH_C_4(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)
#define XI_FOREACH_C_5(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)
#define XI_FOREACH_C_6(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)
#define XI_FOREACH_C_7(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)
#define XI_FOREACH_C_8(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)
#define XI_FOREACH_C_9(M, A, R...)            M(A), XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)

#define XI_FOREACH_C(M, R...)                 XI_CAT(XI_FOREACH_C_, XI_NARGS(R))(M, ##R)

#define XI_SILENCE_UNUSED_WARN(X)             static_cast<void>(X)

#define XI_UNUSED(X...)                       XI_FOREACH_C(XI_SILENCE_UNUSED_WARN, ##X)

// {{{ attr-*

#define attr_ctrl(...)          __attribute__((__VA_ARGS__))

#define spec_visisbility_default     visibility("default")
#define spec_visisbility_hidden      visibility("hidden")

#define attr_export             attr_ctrl(spec_visisbility_default)
#define attr_local              attr_ctrl(spec_visisbility_hidden)
#define attr_unused             attr_ctrl(unused)
#define attr_use_ret            attr_ctrl(warn_unused_result)
#define attr_packed             attr_ctrl(packed)
#define attr_init(prio)         attr_ctrl(constructor(prio))
#define attr_fini(prio)         attr_ctrl(destructor(prio))
#define attr_init_default       attr_init(XI_INIT_PRIO_DEFAULT)
#define attr_fini_default       attr_fini(XI_INIT_PRIO_DEFAULT)

#define XI_INIT_PRIO_INTERNAL   (50000)
#define XI_INIT_PRIO_DEFAULT    (XI_INIT_PRIO_INTERNAL + 1000 + 1)

// }}}

// {{{ misc
#define XI_IMPL_CLASS(Class) XI_JOIN(Class, _Impl)

#define XI_PIMPL(Class)              \
  class XI_IMPL_CLASS(Class);        \
  friend class XI_IMPL_CLASS(Class); \
  Ptr<XI_IMPL_CLASS(Class)> pimpl


// Member Detector
// from https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector

#define XI_GENERATE_HAS_MEMBER_DETECTOR(member)                     \
namespace details {                                                 \
template <class T>                                                  \
struct XI_JOIN(has_member_, member, _checker)                       \
{                                                                   \
  struct fallback { int member; };                                  \
  struct derived : public T, fallback { };                          \
                                                                    \
  template <class U>                                                \
  static std::false_type test(decltype(U::member) *);               \
  template <class U>                                                \
  static std::true_type  test(...);                                 \
                                                                    \
  using result_type = decltype(test<derived>(nullptr));             \
                                                                    \
  constexpr static bool value = result_type::value;                 \
};                                                                  \
} /* namespace details */                                           \
                                                                    \
template <class T>                                                  \
struct XI_JOIN(has_member_, member, _checker)                       \
  : details::XI_JOIN(has_member_, member, _checker)<T>::result_type \
{ }

#define XI_GENERATE_HAS_TYPEDEF_DETECTOR(type)                     \
namespace details {                                                \
template <class T>                                                 \
struct XI_JOIN(has_typedef_, type, _checker)                       \
{                                                                  \
  struct fallback { struct type { }; };                            \
  struct derived : public T, fallback { };                         \
                                                                   \
  template <class U>                                               \
  static std::false_type test(typename U::type *);                 \
  template <class U>                                               \
  static std::true_type  test(...);                                \
                                                                   \
  using result_type = decltype(test<derived>(nullptr));            \
                                                                   \
  constexpr static bool value = result_type::value;                \
};                                                                 \
} /* namespace details */                                          \
                                                                   \
template <class T>                                                 \
struct XI_JOIN(has_typedef_, type, _checker)                       \
  : details::XI_JOIN(has_typedef_, type, _checker)<T>::result_type \
{ }

// }}}

#endif // end of include guard: PP_H_INCLUDED_PI681K2O

