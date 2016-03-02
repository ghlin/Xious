#ifndef CHAIN_H_INCLUDED_AMEDFIP8
#define CHAIN_H_INCLUDED_AMEDFIP8

namespace Xi {

template <class B, class D>
class With : public B
{
public:
  using Super = B;
  using This  = D;
};

namespace details {

template <class With, class Addon, class ...Rest>
class chain_impl
  : public Addon::template Apply<chain_impl<With, Rest...>, typename With::This>
{
protected:
  using Chain_Prev = typename Addon::template Apply<chain_impl<With, Rest...>, typename With::This>;

  using Super = chain_impl;
public:
  using Chain_Prev::Chain_Prev;
};

struct End_Of_Chain_Tag;

template <class With>
class chain_impl<With, End_Of_Chain_Tag>
  : public With::Super
{
protected:
  using Super = chain_impl;

  using Chain_Prev = typename With::Super;
  using Chain_Root = typename With::Super;
public:
  using Chain_Prev::Chain_Prev;
};

} // namespace details

template <class ...C>
using chain = details::chain_impl<C..., details::End_Of_Chain_Tag>;


template <template <class, class> class F>
struct Make_Addon
{
  template <class B, class D>
  using Apply = F<B, D>;
};

} // namespace Xi

#endif // end of include guard: CHAIN_H_INCLUDED_AMEDFIP8

