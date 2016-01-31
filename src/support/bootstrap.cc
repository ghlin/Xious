#include "bootstrap.h"

namespace Xi { namespace init {

Init_Group *bootstrap_root()
{
  static auto *root = new Init_Group("__BOOTSTRAP_MGR__");

  return root;
}



void bootstrap_initialize()
{
  bootstrap_root()->initialize();
}



void bootstrap_finalize()
{
  bootstrap_root()->finalize();

  delete bootstrap_root();
}

} // namespace init
} // namespace Xi

