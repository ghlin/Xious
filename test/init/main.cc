#include "../../src/support/init.h"
#include "../../src/support/bootstrap.h"

XI_BOOTSTRAP_SCOPE()
{
  Xi_log("foo");

  Xi::init::bootstrap_add_task("foo", { "bar" }, [] (const Xi::Str_List &args,
                                                     const Xi::Str      &path)
                               {
                                 Xi_log("[%s]", path);
                               });
}

XI_BOOTSTRAP_SCOPE()
{
  Xi_log("bar");

  Xi::init::bootstrap_add_task("bar", { }, [] (const Xi::Str_List &args,
                                               const Xi::Str      &path)
                               {
                                 Xi_log("[%s]", path);
                               });
}

int main(int argc, const char **argv)
{
  Xi::init::bootstrap_initialize(argc, argv);

  Xi::init::bootstrap_finalize();

  return 0;
}


