#ifndef ROTATE_H_INCLUDED_8WWKOUMD
#define ROTATE_H_INCLUDED_8WWKOUMD

#include "../task.h"
#include "../valueprovider.h"

namespace Xi {

class Rotate : public Task
{
  using Super = Task;
protected:
  Handle<Task>           motion;
  Handle<Value_Provider> angle;
public:
  // (ghlin) : reminder 2016-02-14 19:23:28
};

} // namespace Xi

#endif // end of include guard: ROTATE_H_INCLUDED_8WWKOUMD

