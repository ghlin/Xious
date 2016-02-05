#ifndef PROXY_H_INCLUDED_XDMHS5JX
#define PROXY_H_INCLUDED_XDMHS5JX

#include "../component.h"

namespace Xi {

template <class X>
class X_Proxy : public X_Component<X>
{
public:
  enum Exports : size_t
  {
    X_Proxee = Component_Interface_Exports::X_First_IDX
  };

  inline void set_proxee(X_Component<X> *proxee)
  {
    proxee->retain();
    x_slots[Exports::X_Proxee] = proxee;
  }

  inline X_Component<X> *get_proxee() const
  {
    return static_cast<X_Component<X> *>(x_slots[Exports::X_Proxee]);
  }

};

} // namespace Xi

#endif // end of include guard: PROXY_H_INCLUDED_XDMHS5JX

