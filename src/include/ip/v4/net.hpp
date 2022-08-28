#ifndef __NET_4_HH
#define __NET_4_HH

#include "ip/v4/ip.hpp"
#include "ip/v4/mask.hpp"
#include "ip/base/net_t.hpp"

namespace IP
{
    using NET4 = NET<uint32_t>;

    template <>
    NET4::NET(IP4 addr);
}

#endif