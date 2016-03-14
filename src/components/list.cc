#include "list.h"

namespace Xi {

bool Wait_All_List::complete() const
{
  if (iterated)
    return done;

  iterated = true;
  done     = true;

  for (auto &&task : list)
    if (!task->complete())
    {
      done = false;
      break;
    }

  return done;
}

void Wait_All_List::rewind()
{
  for (auto &&task : list)
    task->rewind();

  iterated = false;
  done     = false;
}

void Wait_All_List::update_routine(const Xi::Update_Details &ud)
{
  iterated = true;
  done     = true;

  for (auto &&task : list)
  {
    task->update(ud);

    if (!task->complete())
      done = false;
  }
}

bool Wait_Any_List::complete() const
{
  if (iterated)
    return done;

  iterated = true;
  done     = false;

  for (auto &&task : list)
    if (task->complete())
    {
      done = true;
      break;
    }

  return done;
}

void Wait_Any_List::rewind()
{
  for (auto &&task : list)
    task->rewind();

  iterated = false;
  done     = false;
}

void Wait_Any_List::update_routine(const Xi::Update_Details &ud)
{
  iterated = true;
  done     = false;

  for (auto &&task : list)
  {
    task->update(ud);

    if (!task->complete())
      done = true;
  }
}
} // namespace Xi

