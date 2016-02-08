#include "../../src/support/bootstrap.h"

using namespace Xi;
using namespace init;

XI_BOOTSTRAP_SCOPE()
{
  bootstrap_add_task("test", { },
                     [] (const Str_List &args, const Str &path)
                     {
                       Xi_log("bootstrap : %s", path);

                       for (auto &&arg : args)
                         Xi_log("  %s", arg);
                     });
}

int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;

  Xi::init::bootstrap_initialize(argc, argv);

  Xi::init::bootstrap_finalize();

  return 0;
}



