#ifndef IFDEBUG_H_INCLUDED_FQK7BHGB
#define IFDEBUG_H_INCLUDED_FQK7BHGB

#include "base.h"

#define XI_DEBUG_MODE   1
#define XI_RELEASE_MODE 0

#if defined(DEBUG) || !defined(RELEASE)
#define XI_DEBUG   1
#define XI_MODE    XI_DEBUG_MODE
#else
#define XI_RELEASE 1
#define XI_MODE    XI_RELEASE_MODE
#endif

#define Xi_log(...)   Xi::tracef(XI_THIS_LOCATION(), __VA_ARGS__)

#define Xi_runtime_check(expr)                       \
  do { if (!(expr)) throw std::runtime_error(        \
    "Assertion failed : `" XI_STRINGIFY(expr) "'!"); \
  } while (false)

#define Xi_die(y)                                 \
  do { throw std::runtime_error(Xi::u_stringify(y)); } while (false)

#define Xi_debug_if(x)   if (!(x)) { } else

#if defined(XI_DEBUG)
/*
 * DEBUG MODE HERE
 */

#define Xi_debug_check(expr)  Xi_runtime_check(expr)
#define Xi_debug_log(...)     Xi_log(__VA_ARGS__)
#define Xi_debug_only         if (false) { } else
#define Xi_debug_cast         dynamic_cast

#else

#define Xi_debug_check(expr)  do { } while (false)
#define Xi_debug_log(...)     do { } while (false)
#define Xi_debug_only         if (true) { } else
#define Xi_debug_cast         static_cast

#endif

namespace Xi {

struct Src_Location
{
  unsigned    line;
  const char *file;
  const char *func;
  const char *pretty_func;

  inline Str dump() const
  {
    return "[ File: "s + u_stringify(file)
      +    ", Line: "s + u_stringify(line)
      +    ", Func: "s + u_stringify(func)
      +    " ]";
  }
};

#define XI_THIS_LOCATION() \
  ::Xi::Src_Location    {  \
    __LINE__,              \
    __FILE__,              \
    __func__,              \
    __PRETTY_FUNCTION__ }

namespace details {

template <class T>
static inline
std::enable_if_t<!std::is_class<std::decay_t<T>>::value, const T &>
xprt_fwd(const T &t) { return t; }



template <size_t N>
static inline
const char *xprt_fwd(const char (&str)[N]) { return str; }



static inline
const char *xprt_fwd(const Str &str)
{ return str.c_str(); }



static inline
const char *xprt_fwd(const Str_View &str)
{ return str.data(); }


} // namespace details

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"

namespace details {

template <typename ...Args>
static inline
auto xprintf_impl(std::FILE     *stream,
                   const Args &...fmt_and_args)
{
  return std::fprintf(stream, fmt_and_args...);
}



template <typename ...Args>
static inline
Str xprintf_impl(const Args &...fmt_and_args)
{
  auto size = std::snprintf(nullptr, 0, fmt_and_args...);

  constexpr decltype(size) DEFAULT_CAPACITY = 512;

  Xi_debug_check (size <= DEFAULT_CAPACITY);

  char buff[DEFAULT_CAPACITY + 1];
  std::snprintf(buff, DEFAULT_CAPACITY, fmt_and_args...);

  return buff;
}

} // namespace details

#pragma GCC diagnostic pop

template <typename ...Args>
static inline
auto xprintf(const Args          &...args)
{
  return details::xprintf_impl(details::xprt_fwd(args)...);
}



template <typename ...Args>
static inline
void tracef(const Src_Location     &sl,
            const Args          &...fmt_and_args)
{
  xprintf(stderr, "[ %s, %s, %u ] - ", sl.file, sl.func, sl.line);
  xprintf(stderr, fmt_and_args...);
  xprintf(stderr, "\n");
}



} // namespace Xi



#endif // end of include guard: IFDEBUG_H_INCLUDED_FQK7BHGB


