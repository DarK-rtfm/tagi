#include "ip/v4/mask.hpp"
#include "ip/base/mask_t.hpp"
#include "sstream"

namespace IP {

template <> MASK4::MASK(const std::string &str) : value(0) {
  std::stringstream stream(str);

  for (auto part : {3, 2, 1, 0}) {
    int tmp = 0;
    stream >> tmp;
    value += (uint8_t)tmp << (8 * part);
    if (part != 0) {
      stream.ignore();
    }
  }
}

template <> std::string MASK4::toString(char _flags) {
  std::ostringstream str;
  for (auto part : {3, 2, 1, 0}) {
    str << (getBitmask() << ((3 - part) * 8) >> ((3 - part) * 8) >> (part * 8));
    if (part != 0) {
      str << '.';
    }
  }
  return str.str();
}
} // namespace IP
