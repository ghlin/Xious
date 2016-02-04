#ifndef CONTAINER_H_INCLUDED_4RUDBY3P
#define CONTAINER_H_INCLUDED_4RUDBY3P

#include "../config.h"
#include "../component.h"

namespace Xi {

namespace policy {

template <class X, class Container>
struct Common_Operations
{
  inline       X *at(      Container &container, size_t idx) const { return container.storage().at(idx); }
  inline const X *at(const Container &container, size_t idx) const { return container.storage().at(idx); }

  inline       X *front(      Container &container) const { return container.storage().front(); }
  inline const X *front(const Container &container) const { return container.storage().front(); }

  inline       X *back(      Container &container) const { return container.storage().back(); }
  inline const X *back(const Container &container) const { return container.storage().back(); }

  inline bool   empty(const Container &container)          const { return container.storage().empty(); }

  inline void   inc(      Container &container)           const { }
  inline void   inc(      Container &container, size_t n) const { }

  inline void   dec(      Container &container)           const { }
  inline void   dec(      Container &container, size_t n) const { }

  inline size_t size(const Container &container)     const { return container.storage()size(); }

  inline size_t capacity(const Container &container) const { return container.storage().capacity(); }

  inline auto   begin(      Container &container) const   { return std::  begin(container.storage()); }
  inline auto   begin(const Container &container) const   { return std::  begin(container.storage()); }
  inline auto  rbegin(      Container &container) const   { return std:: rbegin(container.storage()); }
  inline auto  rbegin(const Container &container) const   { return std:: rbegin(container.storage()); }
  inline auto  cbegin(const Container &container) const   { return std:: cbegin(container.storage()); }
  inline auto crbegin(const Container &container) const   { return std::crbegin(container.storage()); }

  inline auto   end(      Container &container) const   { return std::  end(container.storage()); }
  inline auto   end(const Container &container) const   { return std::  end(container.storage()); }
  inline auto  rend(      Container &container) const   { return std:: rend(container.storage()); }
  inline auto  rend(const Container &container) const   { return std:: rend(container.storage()); }
  inline auto  cend(const Container &container) const   { return std:: cend(container.storage()); }
  inline auto crend(const Container &container) const   { return std::crend(container.storage()); }

  inline void append(Container &container, X *x) const
  {
    x->retain();
    container.storage().push_back(x);
  }

  inline void erase(Container &container, size_t idx) const
  {
    container.storage().erase(begin(container) + idx);
  }

  inline void replace(Container &container, size_t idx, X *component) const
  {
    if (auto *p = at(container, idx))
      p->release();

    component->retain();
  }
};

template <class X, size_t N>
struct Fixed_Storage
{
  using container_type = std::array<X *, N>;

  container_type storage = { };
  size_t         last    = { };

  enum _ : size_t { capacity = N };

  template <typename Iter>
  Fixed_Storage(Iter first, Iter last)
    : storage(first, last)
    , last(std::distance(first, last))
  { }

  inline       container_type &storage()       { return the_storage; }
  inline const container_type &storage() const { return the_storage; }
};

template <class X>
struct Dynamic_Storage
{
  std::vector<X *>   the_storage;

  template <typename Iter>
  Dynamic_Storage(Iter first, Iter last)
    : storage(first, last)
  { }


  inline       container_type &storage()       { return the_storage; }
  inline const container_type &storage() const { return the_storage; }
};

template <class X, class Container>
struct Fixed_Storage_Operations : Common_Operations<X, Container>
{
  // TODO(ghlin) : 2016-02-03 20:51:50
};

template <class X, class Container>
struct Dynamic_Storage_Operations : Common_Operations<X, Container>
{ };

} // namespace policy

template <class X, class S, class O>
class Component_Container : public Component
{
  S        storage;
  O        operation;
public:

};

} // namespace Xi

#endif // end of include guard: CONTAINER_H_INCLUDED_4RUDBY3P

