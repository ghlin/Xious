#include "ifdebug.h"

namespace Xi { namespace details {

Str shortify_path(const Str &path)
{
  auto last_slash = path.rfind('/');

  if (last_slash == path.npos)
    return path;

  return path.substr(last_slash + 1);
}

} // namespace details
} // namespace Xi

