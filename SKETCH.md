
- `Task`不持有Position/Velocity信息, 如果某个task要改变entity的物理信息, 直接操作`Entity::stage`, 以`Entity::commit`应用变化.
  ``` c++
  class Move_To : public Implements<Task, Move_To>
  {
    /* ... */
    void update_logic(const Update_Details &ud) override final
    {
      auto entity = ud.entity;

      entity->stage->set_x_pos(x_pos_lerp(time_elpased));
      entity->stage->set_y_pos(y_pos_lerp(time_elpased));
    }
  };

  class Committor : public Implements<Task, Committor>
  {
    /* ... */
    void update_logic(const Update_Details &ud) override final
    {
      ud.entity->commit();
    }
  };
  ```
- 对应的, `Entity`提供Status/Stage两组状态信息, 前者将应用于碰撞检测/渲染, 后者是这次更新的结果, 在更新后通过`Entity::commit`将Stage提交到Status, 并将Stage重置.
- `Task`增加`rewind`方法.
- 不再使用`std::shared_ptr`作为Handle, 使用`Boost.Intrusive_Ptr`并增加Clone拷贝的包装.
  ``` c++
  template <typename T>
  class Clone_Handle : public Intrusive_Ptr<Obj>
  {
    /* ... */
    Clone_Handle(const Clone_Handle &another)
      : the_ptr(another->clone())
    { }
  };
  ```
- `Composed_Task`一般化为`Task_Queue`
  ``` c++
  class Task_Queue : public Implements<Task, Task_Queue>
  {
    /* ... */
    void update_logic(const Update_Details &ud) override final
    {
      queue.erase_if([=] (auto &task)
      {
        task->update(ud);

        return task->is_complete();
      });
    }
  };
  ```

