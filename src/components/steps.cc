#include "steps.h"

namespace Xi {

void Steps::update_routine(const Update_Details &ud)
{
  while (!reached_eol() && (*current)->complete())
    ++current;

  if (reached_eol())
    return;

  (*current)->update(ud);

  // XXX: this is ugly
  // 2016-03-16 18:38:01
  while (!reached_eol() && (*current)->complete())
    ++current;
}

void Steps::rewind()
{
  current = list.begin();

  for (auto &step : list)
    step->rewind();
}

} // namespace Xi

