#ifndef BASE_H_INCLUDED_0VYM5UQO
#define BASE_H_INCLUDED_0VYM5UQO

#include "pp.h"
#include "stdincl.h"

namespace Xi {

// {{{ basic types
using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;

using std::size_t;

template <typename T>
using Opt = std::experimental::optional<T>;

using Str          = std::string;
using Str_View     = std::experimental::string_view;

using Str_List      = std::vector<Str>;
using Str_View_List = std::vector<Str_View>;

using namespace std::string_literals;

template <typename ...T>
using Arc = std::shared_ptr<T...>;

template <typename ...T>
using Wrc = std::weak_ptr<T...>;

template <typename ...T>
using Ptr = std::unique_ptr<T...>;

// }}}



// {{{ u_* utilities

// {{{ map
template < template <typename ...> class Container = std::vector
         , typename Input
         , typename Lambda
         >
static inline
auto u_map(const Input  &input,
           Lambda      &&lambda)
{
  using Element = std::decay_t<decltype (lambda(*std::cbegin(input)))>;
  using Output  = Container<Element>;

  Output output;
  std::transform(std::cbegin(input),
                 std::cend(input),
                 std::back_inserter(output),
                 std::forward<Lambda>(lambda));

  return output;
}



template < template <typename ...> class Container = std::vector
         , typename Element
         , typename Lambda
         >
static inline
auto u_map(const std::initializer_list<Element>  &input,
           Lambda                               &&lambda)
{
  using Output  = Container<Element>;

  Output output;
  std::transform(std::cbegin(input),
                 std::cend(input),
                 std::back_inserter(output),
                 std::forward<Lambda>(lambda));

  return output;
}

// }}}

// {{{ filter
template < class    Container
         , typename Lambda
         >
static inline
auto u_filter_cp(const Container  &input,
                 Lambda          &&lambda)
{
  Container output;

  auto out_iter = std::back_inserter(output);

  for (auto &&ele : input)
    if (std::forward<Lambda>(lambda)(ele))
      out_iter = ele;

  return output;
}



template < class    Container
         , typename Lambda
         >
static inline
auto u_filter_inp(Container  &input,
                  Lambda    &&lambda)
{
  input.erase(std::remove_if(std::begin(input),
                             std::end(input),
                             std::forward<Lambda>(lambda)));

  return input;
}



template < typename T
         , typename Lambda
         >
static inline
auto u_filter_inp(std::list<T>  &input,
                  Lambda       &&lambda)
{
  input.remove_if(std::begin(input),
                  std::end(input),
                  std::forward<Lambda>(lambda));

  return input;
}

// }}}

// {{{ fold
template < typename Output
         , typename Input
         , typename Lambda
         >
static inline
Output u_foldl(Output        output,
               const Input  &input,
               Lambda      &&lambda)
{
  for (auto &&ele : input)
    lambda(output, ele);

  return output;
}



template < typename Output
         , typename Input
         , typename Lambda
         >
static inline
Output u_foldr(Output        output,
               const Input  &input,
               Lambda      &&lambda)
{
  for (auto iter = std::crbegin(input); iter != std::crend(input); ++iter)
    lambda(output, *iter);

  return output;
}



template < typename Output
         , typename Element
         , typename Lambda
         >
static inline
Output u_foldl(Output                                 output,
               const std::initializer_list<Element>  &input,
               Lambda                               &&lambda)
{
  for (auto &&ele : input)
    lambda(output, ele);

  return output;
}



template < typename Output
         , typename Element
         , typename Lambda
         >
static inline
Output u_foldr(Output                                 output,
               const std::initializer_list<Element>  &input,
               Lambda                               &&lambda)
{
  for (auto iter = std::crbegin(input); iter != std::crend(input); ++iter)
    lambda(output, *iter);

  return output;
}

// }}}

// {{{ find / has
template <class T, class K>
static inline
auto u_find(const T &c, const K &k)
{
  using mapped_type = typename T::mapped_type;

  auto found = c.find(k);

  if (found == c.end())
    return Opt<mapped_type>();

  return Opt<mapped_type>(found->second);
}

template <class T, class K>
static inline
bool u_has(const T &c, const K &k)
{
  return c.find(k) != c.end();
}

// }}}

// {{{ stringify
namespace details {

template <typename T>
static inline
std::enable_if_t<std::is_integral<T>::value, Str>
u_stringify_impl(T t)
{
  return std::to_string(t);
}

template <typename ...Args>
static inline
std::enable_if_t<std::is_constructible<Str, Args...>::value, Str>
u_stringify_impl(Args &&...args)
{
  return Str(std::forward<Args>(args)...);
}

template <typename T>
static inline
std::enable_if_t<!std::is_constructible<Str, T>::value && !std::is_integral<T>::value , Str>
u_stringify_impl(const T &t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

} // namespace details


template <typename ...Args>
static inline
Str u_stringify(Args &&...args)
{
  return details::u_stringify_impl(std::forward<Args>(args)...);
}

// }}}

// {{{ split / trim / join
template <template <typename ...> class Container = std::vector>
static inline
Container<Str> u_split(const Str &input, const Str &sep)
{
  Container<Str> output;


  Str::size_type npos = Str::npos, f = 0, s = 0;
  auto           iter = std::back_inserter(output);

  while ((s = input.find_first_not_of(sep, f)) != npos)
  {
    f    = input.find_first_of(sep, s);
    iter = input.substr(s, f - s);
  }

  return output;
}



static inline
Str u_trim_left(const Str &poor_guy)
{
  auto pos = poor_guy.find_first_not_of(" \t\n");

  return pos == Str::npos ? Str() : poor_guy.substr(pos);
}



static inline
Str u_trim_right(const Str &poor_guy)
{
  auto pos = poor_guy.find_last_not_of(" \t\n");

  return pos == Str::npos ? Str() : poor_guy.substr(0, pos + 1);
}



static inline
Str u_trim(const Str &poor_poor_guy)
{
  return u_trim_right(u_trim_left(poor_poor_guy));
}



template <class Input, class Lambda = std::function<Str (const Str &)>>
static inline
Str u_join(const Input &input,
           const Str   &sep,
           Lambda     &&lambda = [] (const Str &x) { return x; })
{
  auto iter = std::cbegin(input);
  if (iter == std::cend(input))
    return {};

  Str out = lambda(*iter++);

  while (iter != std::cend(input))
  {
    out += sep;
    out += lambda(*iter++);
  }

  return out;
}

// }}}

// }}}

} // namespace Xi

#define XI_IMPL_CLASS(Class) XI_JOIN(Class, _Impl)

#define XI_PIMPL(Class)              \
  class XI_IMPL_CLASS(Class);        \
  friend class XI_IMPL_CLASS(Class); \
  Ptr<XI_IMPL_CLASS(Class)> pimpl;   \


#endif // end of include guard: BASE_H_INCLUDED_0VYM5UQO

