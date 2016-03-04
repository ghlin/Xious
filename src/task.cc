#include "task.h"

namespace Xi {

bool Task::complete() const
{
  return false;
}

bool Task::can_rewind() const
{
  return false;
}

void Phased_Task::before_update_routine(const Update_Details &)
{ }

void Phased_Task::after_update_routine(const Update_Details &)
{ }

} // namespace Xi

