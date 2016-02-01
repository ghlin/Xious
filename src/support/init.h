#ifndef INIT_H_INCLUDED_09P7NEXA
#define INIT_H_INCLUDED_09P7NEXA

#include "../config.h"

namespace Xi { namespace init {

class Init_Node;
using Dep_List = std::set<Str>;

// {{{ Exceptions
class Init_Error : public std::runtime_error
{
public:
  using std::runtime_error::runtime_error;
};



class Init_Already_Finished : public Init_Error
{
public:
  Init_Already_Finished(const Str &operation);
};



class Dependences_Unsatisfied : public Init_Error
{
public:
  Str_List         dependences;

  Dependences_Unsatisfied(const std::vector<Init_Node *> &deps);
};



class Duplicated_Init_Node : public Init_Error
{
public:
  Duplicated_Init_Node(const Str &name);

  Str              duplicated_node;
};
// }}}

class Init_Group;

/**
 * 初始化节点.
 */
class Init_Node : cc::Disable_Copy
{
  friend class Init_Group;

  Str       name; ///< 节点名字, 将作为在初始化组内标识节点的唯一标志.
  Dep_List  deps; ///< 依赖的节点名字.
public:
  Init_Node(const Str &name, const Dep_List &deps);

  virtual ~Init_Node();

  /**
   * 执行初始化动作.
   */
  virtual void initialize() = 0;

  /**
   * 执行注销动作.
   */
  virtual void finalize()   = 0;

  /**
   * 取得节点的名字.
   */
  inline
  const Str &get_name() const { return name; }

  /**
   * 取得节点的依赖.
   */
  inline
  const Dep_List &get_dependences() const { return deps; }

  /**
   * 文字呈现, 调试用.
   */
  virtual Str dump() const;
};


using Init_Function = std::function<void (Init_Node * /* self */)>;

/**
 * 默认动作. 什么也不干.
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
  class _Init_Node : public Init_Node
  {
    Init_Function initializer, finalizer;

  public:
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
 * 根据\param desc的描述构建节点.
 * \param desc  由`,'或`;`分割的串. 第一项是节点名字, 剩余项是依赖(可以为空).
 */
attr_export
Ptr<Init_Node> make_init_node_from_descstr(
  const Str      &desc,
  Init_Function   initializer = Default_Init_Node_Init(),
  Init_Function   finalizer   = Default_Init_Node_Init());



/**
 * 初始化组.
 */
class Init_Group : public Init_Node
{
  XI_PIMPL(Init_Group);

public:
  Init_Group(const Str &name, const Dep_List &deps = { });
  ~Init_Group();

  /**
   * 向组内添加节点, 不必在此时满足依赖关系.
   * \note 添加重复节点会抛出Duplicated_Init_Node异常.
   * \note 调用过initialize以后, 调用此方法会抛出Init_Already_Finished异常.
   */
  virtual Init_Group *register_node(Ptr<Init_Node> &&init_node);

  /**
   * 以合适的顺序执行初始化动作.
   * \note 存在未满足依赖的节点会抛出Dependences_Unsatisfied异常.
   * \note 重复调用会抛出Init_Already_Finished.
   */
  virtual void initialize() override final;

  /**
   * 以合适的顺序执行注销动作.
   * \note 存在未满足依赖的节点会抛出Dependences_Unsatisfied异常.
   * \note 必须在执行过`initialize'之后才可以调用此方法.
   */
  virtual void finalize()   override final;

  virtual Str dump() const override final;
};



static inline
Ptr<Init_Group> make_init_group(const Str &name)
{
  return std::make_unique<Init_Group>(name);
}



} // namespace init
} // namespace Xi



#endif // end of include guard: INIT_H_INCLUDED_09P7NEXA

