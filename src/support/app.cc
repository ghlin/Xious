#include "app.h"
#include "bootstrap.h"

struct App_Scope
{
  App_Scope(int argc, const char **argv)
  {
    Xi::init::bootstrap_initialize(argc, argv);
  }
  ~App_Scope() try
  {
    Xi::init::bootstrap_finalize();
  }
  catch (const std::exception &e)
  {
    Xi_log("Caught: %s :: %s", "Exception", e.what());
  }
  catch (const char *e)
  {
    Xi_log("Caught: %s :: %s", "Message", e);
  }
  catch (const Xi::Str &e)
  {
    Xi_log("Caught: %s :: %s", "Message", e);
  }
  catch (...)
  {
    Xi_log("Caught: ...");
  }
};

int main(int argc, const char **argv) try
{
  auto app = App_Scope(argc, argv);

  // auto result = Xi::App_Main ? Xi::App_Main(argc, argv) : 0;

  return 0;
}
catch (const std::exception &e)
{
  Xi_log("Caught: %s :: %s", "Exception", e.what());
}
catch (const char *e)
{
  Xi_log("Caught: %s :: %s", "Message", e);
}
catch (const Xi::Str &e)
{
  Xi_log("Caught: %s :: %s", "Message", e);
}
catch (...)
{
  Xi_log("Caught: ...");
}



