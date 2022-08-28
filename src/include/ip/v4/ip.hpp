#ifndef __IP_4_HH
#define __IP_4_HH

#include "ip/base/ip_t.hpp"

namespace IP
{
    using IP4 = IP<uint32_t>;
    enum IP4_STR
    {
        DOTTED = 0,
        DEC = 1,
        HEX = 2,
        OCT = 3,
        PAD = 4,
        FILL0 = 8
    };

    template <>
    IP4::IP(std::string str);

    template <>
    std::string IP4::toString(char _flags);
}

#endif