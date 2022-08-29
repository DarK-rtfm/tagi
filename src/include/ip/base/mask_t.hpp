#ifndef __MASK_T_HH
#define __MASK_T_HH

#include <string>

namespace IP {
template <typename T> class MASK {
private:
  uint8_t value{};

public:
  MASK(uint8_t raw);
  MASK(T bitmask);
  MASK(const std::string &str);
  uint8_t getValue();
  T getBitmask();

  std::string toString(char _flags = 0000);

  template <typename U>
  friend bool operator<(const MASK<U> &lhs, const MASK<U> &rhs);
  template <typename U>
  friend bool operator>(const MASK<U> &lhs, const MASK<U> &rhs);
  template <typename U>
  friend bool operator==(const MASK<U> &lhs, const MASK<U> &rhs);
};
template <typename T> MASK<T>::MASK(uint8_t raw) : value(raw) {}

template <typename T> MASK<T>::MASK(T bitmask) {
  throw "CTR not implemented yet.";
}

template <typename T> MASK<T>::MASK(const std::string &str) {
  throw "This CTR is only avaible as specialized.";
}

template <typename T> uint8_t MASK<T>::getValue() { return value; }

template <typename T> T MASK<T>::getBitmask() {
  T bitmask = ~(T)0;
  bitmask <<= sizeof(T) * 8 - value;
  return bitmask;
}

template <typename T> std::string MASK<T>::toString(char _flags) {
  throw "This CTR is only avaible as specialized.";
}

template <typename T> bool operator<(const MASK<T> &lhs, const MASK<T> &rhs) {
  return lhs.value < rhs.value;
}
template <typename T> bool operator>(const MASK<T> &lhs, const MASK<T> &rhs) {
  return lhs.value > rhs.value;
}
template <typename T> bool operator==(const MASK<T> &lhs, const MASK<T> &rhs) {
  return lhs.value == rhs.value;
}

} // namespace IP

#endif
