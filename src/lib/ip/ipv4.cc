#include "ip/ipv4.hh"
#include <format>
#include <iomanip>
#include <ranges>
#include <sstream>

// TODO: use format as soon as libc++ has it.
// #include <format>

namespace IP {
IPv4::IPv4(uint32_t raw) : address(raw) {}

IPv4::IPv4(const std::string &str) {
  std::stringstream stream(str);

  uint32_t value{};
  for (auto part : std::views::iota(0, 4) | std::views::reverse) {
    int tmp = 0;
    stream >> tmp;
    value += (uint8_t)tmp << (8 * part);
    if (part != 0) {
      stream.ignore();
    }
  }
  address = value;
}

std::string IPv4::toString(IPfmt fmt) {
  if (fmt == IPfmt::Dotted) {
    return std::format("{:3}.{:3}.{:3}.{:3}", (address & 0xFF000000) >> 24,
                       (address & 0x00FF0000) >> 16,
                       (address & 0x0000FF00) >> 8,
                       (address & 0x000000FF) >> 0);
  }
  if (fmt == IPfmt::Hex) {
    return std::format("{:x}", address);
  }
  return "";
}

IPclass IPv4::getClass() {
  if (address < 0x80000000)
    return IPclass::A;
  if (address < 0xC0000000)
    return IPclass::B;
  return IPclass::C;
}
} // namespace IP
//}
//
// template class IP<uint32_t>;
//
//} // namespace IP
//
