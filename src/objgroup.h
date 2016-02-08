#ifndef OBJGROUP_H_INCLUDED_JWLXLAQK
#define OBJGROUP_H_INCLUDED_JWLXLAQK

#include "config.h"
#include "object.h"

namespace Xi {

using Obj_List = std::vector<Pooled_Object *>;

class Obj_Group : public Object
{
public:
  Obj_List members;

  inline auto erase(Obj_List::iterator bye)
  {
    (*bye)->release();

    return members.erase(bye);
  }

  /**
   * 删除bye对象, 用最后一个元素填补空缺.
   */
  inline auto unordered_erase(Obj_List::iterator bye)
  {
    auto fill = bye + 1;

    (*bye)->release();

    if (fill == members.end())
      return members.erase(bye);

    *bye  = *fill;
    *fill = nullptr;

    //XXX
    auto off = bye - members.begin();

    members.pop_back();

    return members.begin() + off;
  }

  virtual bool is_qualified(Object *) const;

public:
  inline bool add(Pooled_Object *obj)
  {
    if (!is_qualified(obj))
    {
      // TODO(ghlin) : LOGGING 2016-02-04 21:10:02

      return false;
    }

    unchecked_add(obj);

    return true;
  }

  inline void unchecked_add(Pooled_Object *obj)
  {
    obj->retain();

    members.emplace_back(obj);
  }
};

} // namespace Xi


#endif // end of include guard: OBJGROUP_H_INCLUDED_JWLXLAQK

