#include "init.h"

namespace Xi { namespace init {

Module *make_module_from_descstr(const Str      &desc,
                                 Init_Function   initializer,
                                 Init_Function   finalizer)
{
  auto sep = ":,/";

  auto pos = desc.find_first_of(sep);
  if (pos == Str::npos)
    return make_module(desc, { }, initializer, finalizer);

  auto name = desc.substr(0, pos);
  auto dep_list = u_split(desc.substr(pos + 1), sep);

  return make_module(name, { dep_list.cbegin(), dep_list.cend() }, initializer, finalizer);
}



Module::Module(const Str      &name,
               const Dep_List &deps)
  : name(name)
  , deps(deps)
{ }



Module::~Module()
{ }



Str Module::dump() const
{
  return name + " : [" + u_join(deps, ", ") + "]";
}



class Init_Mgr::Init_Mgr_Impl
{
  using Pkg_List = std::vector<Module *>;

public:
  bool                          closed = false;
  std::set<Str>                 got;
  std::vector<Ptr<Module>>      pool;

  Pkg_List ordered;
  Pkg_List pending;

  static inline bool is_simple_module(const Module *module)
  {
    return module->deps.empty();
  }



  Opt<size_t> try_install(Module *module)
  {
    auto ndeps = module->deps.size();

    for (size_t pos = 0; pos != ordered.size(); ++pos)
    {
      if (u_has(module->deps, ordered.at(pos)->name) && --ndeps == 0)
        return { pos };
    }

    return { };
  }


  void install_module(Module *module, size_t pos)
  {
    ordered.insert(ordered.begin() + pos + 1, module);
  }



  void try_install_pending()
  {
    for (auto iter = pending.begin(); iter != pending.end(); ++iter)
    {
      auto module = *iter;

      if (auto pos = try_install(module))
      {
        install_module(module, *pos);
        pending.erase(iter);

        return try_install_pending();
      }
    }
  }


  void push(Module *module)
  {
    if (closed)
      return;

    if (!got.insert(module->name).second)
      return;

    if (is_simple_module(module))
    {
      ordered.push_back(module);
      try_install_pending();
    }
    else if (auto pos = try_install(module))
    {
      install_module(module, *pos);
      try_install_pending();
    }
    else
    {
      pending.push_back(module);
    }

    pool.emplace_back(module);
  }



  void initialize()
  {
    if (closed)
      return;

    closed = true;

    for (auto *module : ordered)
      module->initialize();
  }



  void finalize()
  {
    if (closed)
      return;

    for (auto pmod = ordered.rbegin(); pmod != ordered.rend(); ++pmod)
      (*pmod)->finalize();
  }
};



Init_Mgr::Init_Mgr(const Str &name, const Dep_List &deps)
  : Module(name, deps)
  , pimpl(new Init_Mgr::Init_Mgr_Impl)
{ }



Init_Mgr::~Init_Mgr()
{ }



Str Init_Mgr::dump() const
{
  return u_join(pimpl->ordered, "\n", [](auto *mod) { return mod->dump(); });
}



Init_Mgr *Init_Mgr::register_module(Module *module)
{
  pimpl->push(module);

  return this;
}



void Init_Mgr::initialize()
{
  pimpl->initialize();
}



void Init_Mgr::finalize()
{
  pimpl->finalize();
}



} // namespace init
} // namespace Xi

