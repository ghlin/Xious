#include "init.h"

namespace Xi { namespace init {

Task_Context::~Task_Context() { }

struct Node;

using Mod_List  = std::vector<Node *>;
using Dep_List  = std::set<Str>;
using Task_List = std::vector<Task>;

enum Node_Status
{
  Waiting,
  Initializing,
  Finalizing,
  Already_Initialized,
  Already_Finalized
};

struct Node
{
  std::set<Ptr<Node>>       pool;
  std::map<Str, Node *>     entries;
  Node                     *root;
  Node                     *parent;
  unsigned                  depth;
  Mod_List                  queue;
  Mod_List                  pending;

  Str                       name;
  Dep_List                  deps;
  Str                       path;

  Ptr<Task_Context>         task_context;

  Task_List                 pre_init,
                            post_init,
                            pre_fini,
                            post_fini;

  Node_Status               node_status;

  bool                      activated;

  Node(const Str &name, const Str_List &deps = { }, bool activated = false)
    : root(this)
    , parent(nullptr)
    , depth(0)
    , name(name)
    , path(name)
    , deps(deps.cbegin(), deps.cend())
    , node_status(Waiting)
    , activated(activated)
  { }

  inline Node *add_entry(Ptr<Node> &&entry)
  {
    auto *save = entry.get();

    pool.insert(std::move(entry));
    entries.emplace(save->name, save);

    save->parent = this;
    save->root   = root;
    save->depth  = depth + 1;

    if (path.empty()) // root -> entry
      save->path   = save->name;
    else
      save->path   = path + "." + save->name;

    return save;
  }

  Node *prepare_path(const Str_List &path, bool active = false)
  {
    Node *iter = this;

    for (auto &&entry : path)
    {
      if (!u_has(iter->entries, entry))
        iter->add_entry(std::make_unique<Node>(entry));

      iter->activated = active;
      iter = iter->entries.at(entry);
    }

    return iter;
  }

  inline Node *prepare_path(const Str &path, bool active = false)
  {
    return prepare_path(u_map(u_split(path, "."), u_trim), active);
  }

  void add_deep_dependence(const Node *dep)
  {
    Xi_runtime_check(root == dep->root);

    Node *node = this;

    while (node->depth > dep->depth)
      node = node->parent;

    while (dep->depth > node->depth)
      dep = dep->parent;

    // until they have the same parent.
    while (node->parent != dep->parent)
    {
      node = node->parent;
      dep  = dep->parent;
    }

    node->deps.insert(dep->name);
  }

  void add_dependence(const Str &depname)
  {
    if (depname.empty())
      throw Init_Error("Invalid name");

    if (depname[0] == '@')
    {
      auto dep = root->prepare_path(depname.substr(1));

      add_deep_dependence(dep);
    }
    else
    {
      deps.insert(depname);
    }
  }

  inline Opt<size_t> test_install(Node *entry)
  {
    auto ndeps = entry->deps.size();

    if (ndeps == 0)
      return { 0 };

    for (size_t pos = 0; pos != queue.size(); ++pos)
    {
      auto that = queue.at(pos);

      if (u_has(entry->deps, that->name) && that->activated && --ndeps == 0)
        return { pos + 1 };
    }

    return { };
  }

  inline void install(Node *entry, size_t pos)
  {
    queue.insert(queue.begin() + pos, entry);
  }

  inline void resolve_pending()
  {
    for (auto iter = pending.begin(); iter != pending.end(); ++iter)
    {
      if (auto pos = test_install(*iter))
      {
        install(*iter, *pos);
        pending.erase(iter);

        return resolve_pending();
      }
    }
  }

  inline void resolve_one(Node *one)
  {
    if (auto pos = test_install(one))
    {
      install(one, *pos);
      resolve_pending();
    }
    else
    {
      pending.push_back(one);
    }
  }

  inline void resolve()
  {
    for (auto &entry : pool)
      resolve_one(entry.get());
  }

  void initialize(Handle *handle)
  {
    if (node_status != Waiting)
      throw Init_Error("Initialize state mismatch.");

    node_status = Initializing;
    auto _ = u_defer_with (this)
    {
      node_status = Already_Initialized;
    };

    resolve();

    if (!pending.empty())
    {
      auto unresolved = u_join(pending, "\n", [] (Node *node)
                              {
                                return node->path + " requires [" + u_join(node->deps, ", ") + "]";
                              });

      auto msg = "Unresolved deps of " + path + " :\n" + unresolved;

      Xi_log(msg);
      Xi_log("pending : %zu", pending.size());

      throw Init_Error(std::move(msg));
    }

    Xi_debug_log(" %s :: %s (needs %zu:%s)",
                 path.empty() ? "<root>" : path,
                 name.empty() ? "<root>" : name,
                 deps.size(),
                 u_join(deps, ", "));

    for (auto &&init : pre_init)
      init(handle, path, name, task_context.get());

    for (auto *entry : queue)
      entry->initialize(handle);

    for (auto &&init : post_init)
      init(handle, path, name, task_context.get());
  }

  void finalize(Handle *handle)
  {
    if (node_status != Already_Initialized)
      throw Init_Error("Finalize state mismatch.");

    node_status = Finalizing;
    auto _ = u_defer_with (this)
    {
      node_status = Already_Finalized;
    };

    for (auto &&fini : pre_fini)
      fini(handle, path, name, task_context.get());

    for (auto pent = queue.rbegin(); pent != queue.rend(); ++pent)
      (*pent)->finalize(handle);

    for (auto &&fini : post_fini)
      fini(handle, path, name, task_context.get());
  }
};

class Handle::Handle_Impl
{
public:
  Ptr<Node> root = std::make_unique<Node>(""); /* root */
};

Handle::Handle() : pimpl(new Handle::Handle_Impl)
{ }

Handle::~Handle() { }

Handle *Handle::active(const Str &path)
{
  auto *node = pimpl->root->prepare_path(path, false);

  node->activated = true;

  return this;
}

Handle *Handle::active_all(const Str &path)
{
  auto *node = pimpl->root->prepare_path(path, true);

  node->activated = true;

  return this;
}

Handle *Handle::add_dependences(const Str &path,
                                const Str_List &deps)
{
  auto *node = pimpl->root->prepare_path(path, false);

  node->activated = true;

  for (auto &&dep : deps)
    node->add_dependence(dep);

  return this;
}

Handle *Handle::append_task(const Str &path,
                            const Str &type,
                            Task       task)
{
  auto node = pimpl->root->prepare_path(path);
  node->activated = true;;

  if (type == "preinit")
    node->pre_init.push_back(task);
  else if (type == "postinit")
    node->post_init.push_back(task);
  else if (type == "prefini")
    node->pre_fini.push_back(task);
  else if (type == "postfini")
    node->pre_fini.push_back(task);
  else
    throw Init_Error("append_task - Unknown type : " + type);

  return this;
}

Handle *Handle::set_task_context(const Str          &path,
                                 Ptr<Task_Context> &&tc)
{
  auto node = pimpl->root->prepare_path(path);
  node->activated = true;

  node->task_context = std::move(tc);

  return this;
}

Task_Context *Handle::get_task_context(const Str &path)
{
  auto node = pimpl->root->prepare_path(path);

  return node->task_context.get();
}

void Handle::initialize()
{
  pimpl->root->initialize(this);
}

void Handle::finalize()
{
  pimpl->root->finalize(this);
}

} // namespace init
} // namespace Xi


