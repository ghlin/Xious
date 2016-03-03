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
  using Args   = std::tuple<R..., details::Dummy, details::Dummy, details::Dummy>;

  using Super  = std::tuple_element_t<0, Args>;
  using Client = std::tuple_element_t<1, Args>;

  using First  = std::tuple_element_t<1, Args>;
  using Second = std::tuple_element_t<2, Args>;
  using Third  = std::tuple_element_t<3, Args>;
};

// add Super typedef.
template <class With, class ...R>
class chain : public details::chain_impl<With, R..., details::End_Of_Chain>::Klass
{
  using Base = typename details::chain_impl<With, R..., details::End_Of_Chain>::Klass;
public:
  using Super = chain;

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

