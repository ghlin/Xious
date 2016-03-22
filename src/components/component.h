#ifndef COMPONENT_H_INCLUDED_P78XZHVN
#define COMPONENT_H_INCLUDED_P78XZHVN

#include "../config.h"
#include "../actor.h"
#include "../task.h"
#include "../valueprovider.h"


namespace Xi {

namespace details {
template < class T
         , class Alt
         , class = std::integral_constant<bool, std::is_same<T, Dummy>::value>
         >
struct Do_Select_Arg
{
  using Type = T;
};

template <class T, class Alt>
struct Do_Select_Arg<T, Alt, std::true_type>
{
  using Type = Alt;
};

template <class T, class Alt>
using Select_Arg = typename Do_Select_Arg<T, Alt>::Type;

} // namespace details

template <class S, class With>
class Obj_List : public S
{
debug_or_protect:
  using Super  = S;
  using Client = typename With::Client;

public:
  using Super::Super;
private:
  struct Fallback
  {
    template <class T>
    using apply = std::vector<T>;
  };
protected:
  using Obj_Type  = details::Select_Arg<typename With::_2, Handle<Task>>;
  using List_Type = typename details::Select_Arg<typename With::_3, Fallback>::template apply<Obj_Type>;

  List_Type list;
public:
  Obj_List() { }

  template <class ...Args>
  Obj_List(Args &&...args)
    : list{ std::forward<Args>(args)... }
  { }

  template <class T>
  Client *append(T &&t)
  {
    list->push_back(std::forward<T>(t));

    return static_cast<Client *>(this);
  }

  size_t size() const
  {
    return list->size();
  }
};


} // namespace Xi

#endif // end of include guard: COMPONENT_H_INCLUDED_P78XZHVN

