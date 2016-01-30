#ifndef INIT_H_INCLUDED_09P7NEXA
#define INIT_H_INCLUDED_09P7NEXA

#include "../config.h"

namespace Xi { namespace init {

using Dep_List = std::set<Str>;

struct Module
{
  const Str       name;
  const Dep_List  deps;

  Module(const Str &name, const Dep_List &deps);
  virtual ~Module();

  virtual void initialize() = 0;
  virtual void finalize()   = 0;

  virtual Str dump() const;
};

using Init_Function = std::function<void (Module * /* self */)>;

struct Default_Module_Init
{
  inline
  void operator ()(Module *) { }
};

static inline
Module *make_module(const Str      &name,
                    const Dep_List &deps,
                    Init_Function   initializer = Default_Module_Init(),
                    Init_Function   finalizer   = Default_Module_Init())
{
  struct _Module : Module
  {
    Init_Function initializer, finalizer;

    virtual void initialize() override final
    { if (initializer) initializer(this); }

    virtual void finalize()   override final
    { if (finalizer) finalizer(this); }

    _Module(const Str &name, const Dep_List &deps,
            Init_Function initializer,
            Init_Function finalizer)
      : Module(name, deps)
      , initializer(initializer)
      , finalizer(finalizer) { }
  };

  return new _Module(name, deps, initializer, finalizer);
}

attr_export
Module *make_module_from_descstr(const Str      &desc,
                                 Init_Function   initializer = Default_Module_Init(),
                                 Init_Function   finalizer   = Default_Module_Init());


class Init_Mgr : public Module
{
  XI_PIMPL(Init_Mgr);

public:
  Init_Mgr(const Str &name, const Dep_List &deps = { });
  ~Init_Mgr();

  Init_Mgr *register_module(Module *module);

  virtual void initialize() override final;
  virtual void finalize()   override final;

  // for debug.
  virtual Str dump() const override final;
};


} // namespace init
} // namespace Xi

#endif // end of include guard: INIT_H_INCLUDED_09P7NEXA

