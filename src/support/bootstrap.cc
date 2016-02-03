#include "bootstrap.h"

namespace Xi { namespace init {


struct Bootstrap_Handle
{
  Ptr<Handle>       handle;
  Str_List          args;

  Bootstrap_Handle()
    : handle(new Handle)
  { }
};

static
Bootstrap_Handle *bootstrap_handle()
{
  static auto *instance = new Bootstrap_Handle;

  return instance;
}

static
Task adapt_task(Bootstrap_Task task)
{
  return [task] (Handle       *,
                 const Str    &path,
                 const Str    &,
                 Task_Context *)
  {
    return task(bootstrap_handle()->args, path);
  };
}


void bootstrap_add_task(const Str       &path,
                        const Str_List  &deps,
                        Bootstrap_Task   task)
{
  bootstrap_handle()->handle
    ->add_dependences(path, deps)
    ->append_task(path, "preinit", adapt_task(task));
}


void bootstrap_add_post_task(const Str       &path,
                             const Str_List  &deps,
                             Bootstrap_Task   task)
{
  bootstrap_handle()->handle
    ->add_dependences(path, deps)
    ->append_task(path, "postinit", adapt_task(task));
}

void bootstrap_add_cleanup(const Str       &path,
                           const Str_List  &deps,
                           Bootstrap_Task   task)
{
  bootstrap_handle()->handle
    ->add_dependences(path, deps)
    ->append_task(path, "postfini", adapt_task(task));
}

void bootstrap_initialize(int argc, const char **argv)
{
  bootstrap_handle()->args = { argv, argv + argc };

  bootstrap_handle()->handle->initialize();
}

void bootstrap_finalize()
{
  bootstrap_handle()->handle->finalize();
}


} // namespace init
} // namespace Xi

