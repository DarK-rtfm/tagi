#ifndef __NET_4_HH
#define __NET_4_HH

#include "ip/base/net_t.hpp"
#include "ip/v4/ip.hpp"
#include "ip/v4/mask.hpp"

namespace IP {
using NET4 = NET<uint32_t>;

template <> NET4::NET(IP4 addr);
} // namespace IP

#endif
