#ifndef PROPERTY_H_INCLUDED_5PMWJSE7
#define PROPERTY_H_INCLUDED_5PMWJSE7

#include "config.h"

namespace Xi {

#ifndef XI_MAGIC_VAR_STORAGE_SIZE
#define XI_MAGIC_VAR_STORAGE_SIZE 32
#endif

constexpr size_t kMagic_Var_Storage_Size = XI_MAGIC_VAR_STORAGE_SIZE;

class Var
{
  uint8_t storage[kMagic_Var_Storage_Size];

  struct Content_Base
  {
    virtual const std::type_info &get_type_info() const = 0;
    virtual void copy_construct_at(void *memo) const = 0;
    virtual void move_construct_at(void *memo)       = 0;

    virtual ~Content_Base() { }
  };

  template <typename T>
  struct Content : Content_Base
  {
    T           the_stuff;

    Content(const Content &c) : the_stuff(c.the_stuff)       { }
    Content(Content &&c) : the_stuff(std::move(c.the_stuff)) { }

    const T &get_the_stuff() const { return the_stuff; }
          T &get_the_stuff()       { return the_stuff; }

    template <class ...Args>
    Content(Args &&...args) : the_stuff(std::forward<Args>(args)...)
    { }

    ~Content()
    { }

    virtual const std::type_info &get_type_info() const override final
    {
      return typeid (T);
    }

    virtual void copy_construct_at(void *memo) const override final
    {
      new (memo) Content(*this);
    }

    virtual void move_construct_at(void *memo) override final
    {
      new (memo) Content(std::move(*this));
    }
  };

  inline const Content_Base *get_content_base() const
  {
    return reinterpret_cast<const Content_Base *>(get_storage());
  }

  inline Content_Base *get_content_base()
  {
    return reinterpret_cast<Content_Base *>(get_storage());
  }

  inline void *get_storage()
  {
    return static_cast<void *>(&storage[0]);
  }

  inline const void *get_storage() const
  {
    return static_cast<const void *>(&storage[0]);
  }

  template <typename T>
  struct Tag { };

  template <class T, class ...Args>
  Var(const Tag<T> &, Args &&...args)
  {
    static_assert(sizeof (Content<T>) <= kMagic_Var_Storage_Size, "Too big for `Var'!");

    new (get_storage()) Content<T>(std::forward<Args>(args)...);
  }
public:
  ~Var()
  {
    get_content_base()->~Content_Base();
  }

  template < class    T
           , class ...Args
           >
  static inline
  Var of(Args &&...args)
  {
    return Var(Tag<T>(), std::forward<Args>(args)...);
  }

  Var(const Var &var)
  {
    var.get_content_base()->copy_construct_at(get_storage());
  }

  Var(Var &&var)
  {
    var.get_content_base()->move_construct_at(get_storage());
  }

  Var() : Var(Tag<std::nullptr_t>()) { }

  inline const std::type_info &get_type_info() const
  {
    return get_content_base()->get_type_info();
  }

  template <typename T>
  inline bool is_of_type() const
  {
    return typeid (T) == get_content_base()->get_type_info();
  }

  template <typename T>
  inline const T &unsafe_get() const
  {
    return static_cast<const Content<T> *>(get_content_base())->get_the_stuff();
  }

  template <typename T>
  inline T &unsafe_get()
  {
    return static_cast<Content<T> *>(get_content_base())->get_the_stuff();
  }

  template <typename T>
  inline const T &get() const
  {
    Xi_runtime_check(is_of_type<T>());

    return unsafe_get<T>();
  }

  template <typename T>
  inline T &get()
  {
    Xi_runtime_check(is_of_type<T>());

    return unsafe_get<T>();
  }

  inline operator bool() const
  {
    return is_of_type<std::nullptr_t>();
  }

  template <typename T>
  inline Var &operator =(const T &val)
  {
    Xi_runtime_check(is_of_type<T>());

    get<T>() = val;

    return *this;
  }

  template <typename T>
  inline Var &operator =(T &&val)
  {
    Xi_runtime_check(is_of_type<T>());

    get<T>() = std::move(val);

    return *this;
  }

  inline Var &operator =(const Var &rhs)
  {
    Xi_runtime_check(get_type_info() == rhs.get_type_info());

    if (this == &rhs)
      return *this;

    // TODO(ghlin) : reminder 2016-02-11 15:46:27

    return *this;
  }


  inline Var &operator =(Var &&rhs)
  {
    Xi_runtime_check(get_type_info() == rhs.get_type_info());

    if (this == &rhs)
      return *this;

    // TODO(ghlin) : reminder 2016-02-11 15:46:27

    return *this;
  }
};


} // namespace Xi


#endif // end of include guard: PROPERTY_H_INCLUDED_5PMWJSE7

