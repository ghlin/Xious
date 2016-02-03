#ifndef INIT_H_INCLUDED_09P7NEXA
#define INIT_H_INCLUDED_09P7NEXA

#include "../config.h"

namespace Xi { namespace init {

class Task_Context
{
public:
  virtual ~Task_Context() = 0;
};

class Handle;

using Task     = std::function<void ( Handle       * /* handle */
                                    , const Str    & /* path */
                                    , const Str    & /* name */
                                    , Task_Context *)>;

class Handle : cc::Disable_Copy
{
  XI_PIMPL(Handle);
public:
  Handle();
  ~Handle();

  Handle *active(const Str &path);

  Handle *active_all(const Str &path);

  Handle *add_dependences(const Str &path,
                          const Str_List &deps);

  Handle *append_task(const Str &path,
                      const Str &type,
                      Task       task);

  Handle *set_task_context(const Str          &path,
                           Ptr<Task_Context> &&tc);

  Task_Context *get_task_context(const Str &path);

  void initialize();

  void finalize();
};

// {{{ Exceptions
class Init_Error : public std::runtime_error
{
public:
  using std::runtime_error::runtime_error;
};
// }}}

} // namespace init
} // namespace Xi



#endif // end of include guard: INIT_H_INCLUDED_09P7NEXA

