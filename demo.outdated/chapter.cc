#include "chapter.h"

namespace Xi {
static
std::vector<Handle<Chapter>> &_chapters()
{
  static std::vector<Handle<Chapter>> _;
  return _;
}

void register_chapter(Handle<Chapter> chapter)
{
  _chapters().push_back(chapter);
}

XI_BOOTSTRAP_SCOPE()
{
  Xi::init::bootstrap_add_task("chapters", { },
                               [] (const Str_List &,
                                   const Str      &)
                               {
                                 std::sort(_chapters().begin(), _chapters().end(),
                                           [] (const auto &lhs, const auto &rhs)
                                           {
                                             return lhs->title < lhs->title;
                                           });
                               });
}

const std::vector<Handle<Chapter>> &get_chapters()
{
  return _chapters();
}


} // namespace Xi

