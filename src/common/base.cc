#include "pp.h"
#include "base.h"
#include <cxxabi.h>

namespace Xi {

Str u_name_demangle(const Str &mangled_name)
{
  auto demangled_name = abi::__cxa_demangle(mangled_name.c_str(), nullptr, nullptr, nullptr);
  auto _ = u_defer_with (demangled_name) { free(demangled_name); };

  return { demangled_name };
}

} // namespace Xi

