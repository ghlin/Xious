#include "bootstrap.h"

namespace Xi { namespace init {

static Handle *bootstrap_handle()
{
  static auto *instance = new Handle;

  return instance;
}

} // namespace init
} // namespace Xi

