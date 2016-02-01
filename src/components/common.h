#ifndef COMMON_H_INCLUDED_QQDBOG0X
#define COMMON_H_INCLUDED_QQDBOG0X

#include "../config.h"
#include "../component.h"

namespace Xi { namespace details {

/**
 * 容器
 */
template < class Component_Type
         , class Container
         >
class Component_Container : public Component_Type
{
protected:
  Container                composed;
public:
  template <typename ...Args>
  Component_Container(Args &&...args)
    : composed(std::forward<Args>(args)...)
  { }

  inline auto begin()          { return std::begin(composed); }
  inline auto end()            { return std::end(composed);   }

  inline auto begin()    const { return std::cbegin(composed); }
  inline auto end()      const { return std::cend(composed);   }

  inline auto cbegin()   const { return std::cbegin(composed); }
  inline auto cend()     const { return std::cend(composed);   }

  inline auto rbegin()         { return std::rbegin(composed); }
  inline auto rend()           { return std::rend(composed);   }

  inline auto rbegin()   const { return std::crbegin(composed); }
  inline auto rend()     const { return std::crend(composed);   }

  inline auto crbegin()  const { return std::crbegin(composed); }
  inline auto crend()    const { return std::crend(composed);   }

  inline bool capacity() const { return composed.capacity(); }
  inline bool empty()    const { return composed.empty();    }
  inline auto size()     const { return composed.size();     }
  inline auto data()     const { return composed.data();     }

  inline auto at(size_t i)       { return composed.at(i); }
  inline auto at(size_t i) const { return composed.at(i); }

  inline auto front()            { return composed.front(); }
  inline auto front()      const { return composed.front(); }

  inline auto back()            { return composed.back(); }
  inline auto back()      const { return composed.back(); }

  inline const auto &get_container() const { return composed; }
  inline       auto &get_container()       { return composed; }
};



template < class  Component_Type
         , size_t Capacity = 0
         >
class Select_Component_Container
  : public Component_Container<Component_Type, std::array<Component_Type *, Capacity>>
{ };



template <class Component_Type>
class Select_Component_Container<Component_Type, 0>
  : public Component_Container<Component_Type, std::vector<Component_Type *>>
{ };



} // namespace details

template <class X> using Component_List     = details::Select_Component_Container<X,  0>;
template <class X> using Component_Proxy    = details::Select_Component_Container<X,  1>;
template <class X> using Component_Pair     = details::Select_Component_Container<X,  2>;
template <class X> using Component_Triple   = details::Select_Component_Container<X,  3>;
template <class X> using Component_Array_8  = details::Select_Component_Container<X,  8>;
template <class X> using Component_Array_16 = details::Select_Component_Container<X, 16>;
template <class X> using Component_Array_32 = details::Select_Component_Container<X, 32>;
template <class X> using Component_Array_64 = details::Select_Component_Container<X, 64>;

} // namespace Xi

#endif // end of include guard: COMMON_H_INCLUDED_QQDBOG0X

