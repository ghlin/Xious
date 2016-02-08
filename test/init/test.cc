#include "../../src/support/bootstrap.h"

XI_BOOTSTRAP_SCOPE()
{
  using namespace Xi;
  using namespace Xi::init;

  bootstrap_add_task("internal.trace.args", { "@internal.trace.nargs" },
                     [] (const Str_List &args, const Str      &path)
                     {
                       for (auto &&arg : args)
                         Xi_log("   %s", arg);
                     });
}

XI_BOOTSTRAP_SCOPE()
{
  using namespace Xi;
  using namespace Xi::init;

  bootstrap_add_task("internal.trace.nargs", { },
                     [] (const Str_List &args, const Str      &path)
                     {
                       Xi_log("%zu args : ", args.size());
                     });
}

