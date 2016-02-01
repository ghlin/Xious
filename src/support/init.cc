#include "init.h"

namespace Xi { namespace init {

// {{{ make node
Ptr<Init_Node> make_init_node_from_descstr(
  const Str      &desc,
  Init_Function   initializer,
  Init_Function   finalizer)
{
  auto sep = ":,/";

  auto pos = desc.find_first_of(sep);
  if (pos == Str::npos)
    return make_init_node(desc, { }, initializer, finalizer);

  auto name = desc.substr(0, pos);
  auto dep_list = u_split(desc.substr(pos + 1), sep);

  return make_init_node(name, { dep_list.cbegin(), dep_list.cend() }, initializer, finalizer);
}

// }}}


// {{{ Init_Node
Init_Node::Init_Node(const Str      &name,
                     const Dep_List &deps)
  : name(name)
  , deps(deps)
{ }



Init_Node::~Init_Node()
{ }



Str Init_Node::dump() const
{
  return name + " : [" + u_join(deps, ", ") + "]";
}

// }}}


// {{{ Init_Group

class Init_Group::Init_Group_Impl
{
  using Pkg_List = std::vector<Init_Node *>;

public:
  bool                             closed = false;
  std::set<Str>                    got;
  std::vector<Ptr<Init_Node>>      pool;

  Pkg_List ordered;
  Pkg_List pending;

  static inline bool is_simple_init_node(const Init_Node *init_node)
  {
    return init_node->deps.empty();
  }


  Opt<size_t> try_install(Init_Node *init_node)
  {
    auto ndeps = init_node->deps.size();

    for (size_t pos = 0; pos != ordered.size(); ++pos)
    {
      if (u_has(init_node->deps, ordered.at(pos)->name) && --ndeps == 0)
        return { pos };
    }

    return { };
  }


  void install_init_node(Init_Node *init_node, size_t pos)
  {
    ordered.insert(ordered.begin() + pos + 1, init_node);
  }



  void try_install_pending()
  {
    for (auto iter = pending.begin(); iter != pending.end(); ++iter)
    {
      auto init_node = *iter;

      if (auto pos = try_install(init_node))
      {
        install_init_node(init_node, *pos);
        pending.erase(iter);

        return try_install_pending();
      }
    }
  }



  void resolve_one(Init_Node *pnode)
  {
    if (is_simple_init_node(pnode))
    {
      ordered.push_back(pnode);
      try_install_pending();
    }
    else if (auto pos = try_install(pnode))
    {
      install_init_node(pnode, *pos);
      try_install_pending();
    }
    else
    {
      pending.push_back(pnode);
    }
  }


  void register_node(Ptr<Init_Node> &&init_node)
  {
    if (closed)
      throw Init_Already_Finished("register_node");

    if (!got.insert(init_node->name).second)
      throw Duplicated_Init_Node(init_node->name);

    pool.emplace_back(std::move(init_node));
  }



  void initialize()
  {
    if (closed)
      throw Init_Already_Finished("initialize");

    closed = true;

    for (auto &&node : pool)
      resolve_one(node.get());

    if (!pending.empty())
      throw Dependences_Unsatisfied(pending);

    for (auto *init_node : ordered)
      init_node->initialize();
  }



  void finalize()
  {
    if (!closed)
      throw Init_Error("`finalize' called before `initialize'.");

    for (auto pnode = ordered.rbegin(); pnode != ordered.rend(); ++pnode)
      (*pnode)->finalize();
  }
};



Init_Group::Init_Group(const Str &name, const Dep_List &deps)
  : Init_Node(name, deps)
  , pimpl(new Init_Group::Init_Group_Impl)
{ }



Init_Group::~Init_Group()
{ }



Str Init_Group::dump() const
{
  return Init_Node::dump() + " \n"
    + u_join(pimpl->ordered, "\n", [](auto *node) { return "  " + node->dump(); });
}



Init_Group *Init_Group::register_node(Ptr<Init_Node> &&init_node)
{
  pimpl->register_node(std::move(init_node));

  return this;
}



void Init_Group::initialize()
{
  pimpl->initialize();
}



void Init_Group::finalize()
{
  pimpl->finalize();
}

// }}}


// {{{ Exceptions

Init_Already_Finished::Init_Already_Finished(const Str &operation)
  : Init_Error("Init already finished when calling `" + operation + "'")
{ }



Dependences_Unsatisfied::Dependences_Unsatisfied(
  const std::vector<Init_Node *> &deps)
  : Init_Error("Unsatisfied dependences found.")
  , dependences(u_map(deps, [] (auto x) { return x->get_name(); }))
{ }


Duplicated_Init_Node::Duplicated_Init_Node(const Str &name)
  : Init_Error("Duplicated init node found: " + name)
  , duplicated_node(name)
{ }

// }}}


} // namespace init
} // namespace Xi

