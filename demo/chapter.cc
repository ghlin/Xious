#include "chapter.h"

namespace Xi {
static
std::list<Handle<Chapter>> &_chapters()
{
  static std::list<Handle<Chapter>> _;
  return _;
}

void register_chapter(Handle<Chapter> chapter)
{
  _chapters().push_back(chapter);
}

const std::list<Handle<Chapter>> &get_chapters()
{
  return _chapters();
}


} // namespace Xi

