#ifndef INIT_H_INCLUDED_09P7NEXA
#define INIT_H_INCLUDED_09P7NEXA

#include "../config.h"

namespace Xi { namespace init {

using Dep_List = std::set<Str>;

/**
 * 初始化节点
 */
struct Init_Node
{
  const Str       name; ///< 节点名字 作为在初始化组内标识节点的唯一标志
  const Dep_List  deps; ///< 这个节点依赖的节点 必须是同一初始化组内 这里指定的节点的初始化动作会在这个节点之前完成

  Init_Node(const Str &name, const Dep_List &deps);

  virtual ~Init_Node();

  /**
   * 执行初始化动作
   */
  virtual void initialize() = 0;

  /**
   * 执行注销动作
   */
  virtual void finalize()   = 0;

  /**
   * 文字呈现 调试用
   */
  virtual Str dump() const;
};


using Init_Function = std::function<void (Init_Node * /* self */)>;

/**
 * 默认动作
 * 什么也不干
 */
struct Default_Init_Node_Init
{
  inline
  void operator ()(Init_Node *) { }
};

static inline
Ptr<Init_Node> make_init_node(const Str      &name,
                              const Dep_List &deps,
                              Init_Function   initializer = Default_Init_Node_Init(),
                              Init_Function   finalizer   = Default_Init_Node_Init())
{
  struct _Init_Node : Init_Node
  {
    Init_Function initializer, finalizer;

    virtual void initialize() override final
    { if (initializer) initializer(this); }

    virtual void finalize()   override final
    { if (finalizer) finalizer(this); }

    _Init_Node(const Str &name, const Dep_List &deps,
            Init_Function initializer,
            Init_Function finalizer)
      : Init_Node(name, deps)
      , initializer(initializer)
      , finalizer(finalizer) { }
  };

  return std::make_unique<_Init_Node>(name, deps, initializer, finalizer);
}

/**
 * 根据\param desc的描述构建节点
 * \param desc  由`,;/`之一分割的串 第一项是节点名字 剩余项是依赖(可以为空)
 */
attr_export
Ptr<Init_Node> make_init_node_from_descstr(
  const Str      &desc,
  Init_Function   initializer = Default_Init_Node_Init(),
  Init_Function   finalizer   = Default_Init_Node_Init());

/**
 * 初始化组
 */
class Init_Group : public Init_Node
{
  XI_PIMPL(Init_Group);

public:
  Init_Group(const Str &name, const Dep_List &deps = { });
  ~Init_Group();

  /**
   * 向组内添加节点 不必在此时满足依赖关系
   */
  Init_Group *register_node(Ptr<Init_Node> &&init_node);

  /**
   * 以合适的顺序执行初始化动作
   * \note 未满足依赖的节点会被忽略
   */
  virtual void initialize() override final;

  /**
   * 以合适的顺序执行注销动作
   * \note 未满足依赖的节点会被忽略
   */
  virtual void finalize()   override final;

  virtual Str dump() const override final;
};


} // namespace init
} // namespace Xi

#endif // end of include guard: INIT_H_INCLUDED_09P7NEXA

