#ifndef __IP_T_HH
#define __IP_T_HH

#include "exceptions.hh"
#include <string>
#include <vector>

namespace IP {

template <typename T> class IP {
private:
  T value;

public:
  IP(T raw);
  IP(const std::vector<uint8_t> &parts);
  IP(const std::string &str);

  T getValue();
  std::string toString(char _flags = 0000);

  template <typename U>
  friend bool operator<(const IP<U> &fst, const IP<U> &snd);
  template <typename U>
  friend bool operator>(const IP<U> &fst, const IP<U> &snd);
  template <typename U>
  friend bool operator==(const IP<U> &fst, const IP<U> &snd);

  friend IP<T> operator+(const IP<T> &derived, const T num) {
    return IP<T>(derived.value + num);
  }
  //  TODO: ADD-MASK operator
};
template <typename T> IP<T>::IP(T raw) : value(raw) {}

template <typename T> IP<T>::IP(const std::vector<uint8_t> & /*unused*/) {
  throw E_TODO;
}

template <typename T> IP<T>::IP(const std::string &str) { throw E_NoSpec(); }

template <typename T> T IP<T>::getValue() { return value; }

template <typename T> std::string IP<T>::toString(char _flags) {
  throw E_NoSpec();
}
template <typename T> bool operator<(const IP<T> &lhs, const IP<T> &rhs) {
  return lhs.value < rhs.value;
}
template <typename T> bool operator>(const IP<T> &lhs, const IP<T> &rhs) {
  return lhs.value > rhs.value;
}
template <typename T> bool operator==(const IP<T> &lhs, const IP<T> &rhs) {
  return lhs.value == rhs.value;
}

template <typename T> IP<T> operator+(const IP<T> &base, const T num) {
  return IP<T>::IP(base.value + num);
}

} // namespace IP

#endif
