#ifndef OBJECT_H_INCLUDED_PE2AN1KV
#define OBJECT_H_INCLUDED_PE2AN1KV

#include "config.h"

namespace Xi {

/**
 * 大部分对象的基类.
 */
class Object
{
public:
  virtual ~Object() = 0;

  virtual void initialize();
  virtual void finalize();
};

/**
 * 池化对象.
 */
class Pooled_Object
  : public Object
{
  ref_count_t ref_count;
public:
  Pooled_Object(const Pooled_Object &) :
    ref_count(0) { }

  Pooled_Object(Pooled_Object &&) :
    ref_count(0) { }

  Pooled_Object() : ref_count(0) { }

  inline
  Pooled_Object &operator =(const Pooled_Object &)
  {
    return *this;
  }

  inline
  Pooled_Object &operator =(Pooled_Object &&other)
  {
    Xi_debug_check(other.get_ref_count() == 1);

    return *this;
  }

  ~Pooled_Object();

  inline ref_count_t retain()
  {
    if (++ref_count == 1)
      initialize();

    return ref_count;
  }

  inline ref_count_t release()
  {
    if (--ref_count == 0)
      finalize();

    return ref_count;
  }

  inline ref_count_t get_ref_count() const
  {
    return ref_count;
  }

  virtual void finalize() override;
};

/**
 * 对象池原型.
 */
class Object_Pool : public Object
{
public:
  virtual Object *acquire()         = 0;
  virtual void    release(Object *) = 0;
};

/**
 * 构建器.
 */
class Object_Creator : public Object
{
public:
  template <class X>
  inline
  X *create_of()
  {
    return static_cast<X *>(create());
  }

  virtual Object *create()          = 0;
  virtual void    destroy(Object *) = 0;
};

/**
 * 默认new/delete构建器.
 */
template <class X>
class X_Object_Creator : public Object_Creator
{
public:
  inline
  virtual Object *create() override final
  {
    return static_cast<Object *>(new X);
  }

  inline
  virtual void   destroy(Object *x) override final
  {
    delete x;
  }
};

} // namespace Xi

#endif // end of include guard: OBJECT_H_INCLUDED_PE2AN1KV

