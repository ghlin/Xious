#include "init.h"

namespace Xi { namespace init {

// {{{ make node
Ptr<Init_Node> make_init_node_from_descstr(
  const Str      &desc,
  Init_Function   initializer,
  Init_Function   finalizer)
{
  auto sep = ",;";
  auto pos = desc.find_first_of(sep);

  if (pos == Str::npos)
    return make_init_node(desc, { }, initializer, finalizer);

  auto name     = desc.substr(0, pos);
  auto dep_list = u_split(desc.substr(pos + 1), sep);

  for (auto &dep : dep_list)
    dep = u_trim(dep);

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



  Opt<size_t> prob_install_pos(Init_Node *node)
  {
    auto ndeps = node->deps.size();

    if (ndeps == 0)
      return { 0 };

    for (size_t pos = 0; pos != ordered.size(); ++pos)
    {
      if (u_has(node->deps, ordered.at(pos)->name) && --ndeps == 0)
        return { pos + 1 };
    }

    return { };
  }



  void do_install(Init_Node *node, size_t pos)
  {
    ordered.insert(ordered.begin() + pos, node);
  }



  void resolve_pending()
  {
    for (auto iter = pending.begin(); iter != pending.end(); ++iter)
    {
      if (auto pos = prob_install_pos(*iter))
      {
        do_install(*iter, *pos);
        pending.erase(iter);

        return resolve_pending();
      }
    }
  }



  void resolve_one(Init_Node *node)
  {
    if (auto pos = prob_install_pos(node))
    {
      do_install(node, *pos);
      resolve_pending();
    }
    else
    {
      pending.push_back(node);
    }
  }



  void register_node(Ptr<Init_Node> &&node)
  {
    if (closed)
      throw Init_Already_Finished("register_node");

    if (!got.insert(node->name).second)
      throw Duplicated_Init_Node(node->name);

    pool.emplace_back(std::move(node));
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

    for (auto *node : ordered)
      node->initialize();
  }



  void finalize()
  {
    if (!closed)
      throw Init_Error("`finalize' called before `initialize'.");

    for (auto node = ordered.rbegin(); node != ordered.rend(); ++node)
      (*node)->finalize();
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



Init_Group *Init_Group::register_node(Ptr<Init_Node> &&node)
{
  pimpl->register_node(std::move(node));

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

