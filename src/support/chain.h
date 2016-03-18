#ifndef CHAIN_H_INCLUDED_AMEDFIP8
#define CHAIN_H_INCLUDED_AMEDFIP8

#include "../config.h"

namespace Xi {

namespace details {

struct Dummy;
struct End_Of_Chain;

template <class With, class I, class ...R>
struct chain_impl
{
  using Klass = typename I::template Apply<typename chain_impl<With, R...>::Klass, With>;
};


template <class With>
struct chain_impl<With, details::End_Of_Chain>
{
  using Klass = typename With::Super;
};

} // namespace details

template <class ...R>
struct With
{
  using Dummy = details::Dummy;

  using Args   = std::tuple<R...,
        Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy>;

  using Super  = std::tuple_element_t<0, Args>;
  using Client = std::tuple_element_t<1, Args>;

  using _0 = std::tuple_element_t<0, Args>;
  using _1 = std::tuple_element_t<1, Args>;
  using _2 = std::tuple_element_t<2, Args>;
  using _3 = std::tuple_element_t<3, Args>;
  using _4 = std::tuple_element_t<4, Args>;
  using _5 = std::tuple_element_t<5, Args>;
  using _6 = std::tuple_element_t<6, Args>;
  using _7 = std::tuple_element_t<7, Args>;
  using _8 = std::tuple_element_t<8, Args>;
  using _9 = std::tuple_element_t<9, Args>;
};

// add Super typedef.
template <class With, class ...R>
class chain : public details::chain_impl<With, R..., details::End_Of_Chain>::Klass
{
debug_or_protect:
  using Base = typename details::chain_impl<With, R..., details::End_Of_Chain>::Klass;
  using Super = chain;

public:
  using Base::Base;
};

template <template <class, class> class F>
struct addin
{
  template <class S, class W>
  using Apply = F<S, W>;
};


} // namespace Xi

#endif // end of include guard: CHAIN_H_INCLUDED_AMEDFIP8

