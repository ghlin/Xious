#ifndef ENTITY_H_INCLUDED_QS1YHTJM
#define ENTITY_H_INCLUDED_QS1YHTJM

#include "task.h"

namespace Xi {

class Entity : public Extends<Actor>
{
public:
  enum Update_Status : uint32_t
  {
    US_Normal,       ///< 参与正常更新
    US_To_Remove,    ///< 指示移除
    US_Skip,         ///< 不参与更新
  };

  std::map<Str, Handle<Object>> components;

  Handle<Collider> collider;
  Handle<Render>   render;
  Handle<Task>     task;
  Update_Status    update_status = US_Normal;

  XI_PROP_EXPORT( (Collider, collider)
                , (Render, render)
                , (Task, task)
                , (Update_Status, update_status)
                , (Components, components)
                );
public:
  Entity() { }

  Entity(Handle<Collider> collider,
         Handle<Render>   render,
         Handle<Task>     task,
         Update_Status    update_status = Update_Status::US_Normal)
    : collider(std::move(collider))
    , render(std::move(render))
    , task(std::move(task))
    , update_status(update_status)
  { }

  virtual void do_collision_test(const Update_Details &ud) = 0;

  virtual void do_render(const Update_Details &ud) = 0;

  inline
  const Handle<Task> &get_task() const
  {
    return task;
  }

  inline
  const Handle<Collider> &get_collider() const
  {
    return collider;
  }

  inline
  const Handle<Render> &get_render() const
  {
    return render;
  }
protected:
  virtual void update(const Update_Details &ud) override
  {
    Xi_debug_check(task);
    Xi_debug_check(collider);
    Xi_debug_check(render);

    task->update(ud);
    collider->update(ud);
    render->update(ud);
  }
};

} // namespace Xi

#endif // end of include guard: ENTITY_H_INCLUDED_QS1YHTJM

