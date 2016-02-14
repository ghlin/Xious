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

    virtual void copy_assignment(const Content_Base *) = 0;
    virtual void move_assignment(Content_Base       *) = 0;

    virtual ~Content_Base() { }
  };

  template <typename T>
  struct Content : Content_Base
  {
    T           the_stuff;

    Content(const Content &c) : the_stuff(c.the_stuff)       { }
    Content(Content &&c) : the_stuff(std::move(c.the_stuff)) { }

    Content &operator =(const Content &) = default;
    Content &operator =(Content      &&) = default;

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

    virtual void copy_assignment(const Content_Base *rhs) override final
    {
      *this = *static_cast<const Content *>(rhs);
    }

    virtual void move_assignment(Content_Base       *rhs) override final
    {
      *this = std::move(*static_cast<Content *>(rhs));
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

  struct Null_Type { };

  template <class T, class ...Args>
  Var(const Tag<T> &, Args &&...args)
  {
    static_assert(sizeof (Content<T>) <= kMagic_Var_Storage_Size, "Danger! Danger!");

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

  Var() : Var(Tag<Null_Type>()) { }

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
    return is_of_type<Null_Type>();
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

    get_content_base()->copy_assignment(rhs.get_content_base());

    return *this;
  }


  inline Var &operator =(Var &&rhs)
  {
    Xi_runtime_check(get_type_info() == rhs.get_type_info());

    if (this == &rhs)
      return *this;

    get_content_base()->move_assignment(rhs.get_content_base());

    return *this;
  }

  inline void clear()
  {
    this->~Var();
    new (this) Var();
  }
};


} // namespace Xi


#endif // end of include guard: PROPERTY_H_INCLUDED_5PMWJSE7

