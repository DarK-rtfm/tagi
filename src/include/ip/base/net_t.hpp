#ifndef __NET_T_HH
#define __NET_T_HH

#include "ip/base/ip_t.hpp"
#include "ip/base/mask_t.hpp"

namespace IP {
template <typename T> class NET {
private:
  IP<T> address;
  MASK<T> mask;

public:
  NET(IP<T> _addr, MASK<T> _mask);
  NET(IP<T> _addr);

  IP<T> getAddress() { return address; }
  MASK<T> getMask() { return mask; }
  bool contains(IP<T> _addr);
};
template <typename T>
NET<T>::NET(IP<T> _addr, MASK<T> _mask) : address(_addr), mask(_mask) {}

template <typename T>
NET<T>::NET(IP<T> _addr) : address(_addr), mask((uint8_t)0) {
  throw E_NoSpec;
}

template <typename T> bool NET<T>::contains(IP<T> _addr) {
  return ((mask.getBitmask() & _addr.getValue()) == address.getValue());
}
} // namespace IP

#endif
