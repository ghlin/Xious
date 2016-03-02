#include "task.h"

using namespace Xi;

int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;

  Task *tsk;
  std::vector<Handle<Task>> t
    =
    {
      handle_cast<Task>(tsk->clone()),
      handle_cast<Task>(tsk->clone()),
      handle_cast<Task>(tsk->clone()),
      handle_cast<Task>(tsk->clone()),
      handle_cast<Task>(tsk->clone()),
    };

  auto r = t;

  return 0;
}

