#include "ip/v4/ip.hpp"
#include "ip/base/ip_t.hpp"
#include <iomanip>
#include <sstream>
// TODO: use format as soon as libc++ has it.
//#include <format>

namespace IP {
template <> IP4::IP(const std::string &str) : value(0) {
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

template <> std::string IP4::toString(char _flags) {
  std::ostringstream str;
  if ((_flags & 3) == IP4_STR::DOTTED) {
    if ((_flags & IP4_STR::FILL0) != 0) {
      str << std::setfill('0');
    }
    for (auto part : {3, 2, 1, 0}) {
      if ((_flags & IP4_STR::PAD) != 0) {
        str << std::setw(3);
      }
      str << (value << ((3 - part) * 8) >> ((3 - part) * 8) >> (part * 8));
      if (part != 0) {
        str << '.';
      }
    }
  } else {
    switch (_flags & 3) {
    case IP4_STR::HEX:
      str << std::hex << "0x";
      break;
    case IP4_STR::OCT:
      str << std::oct << "0";
      break;
    case IP4_STR::DEC:
      str << std::dec;
    }
    str << value;
  }
  return str.str();
}
} // namespace IP
