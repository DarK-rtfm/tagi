#include "ip/v4/net.hpp"
#include "ip/v4/ip.hpp"
#include "ip/v4/mask.hpp"

namespace IP
{
    template <>
    NET4::NET(IP4 addr) : address(addr), mask((uint8_t)0)
    {
        address = addr;
        /**/ if (address < IP(0x80000000))
            mask = MASK4((uint8_t)8);
        else if (address < IP(0xC0000000))
            mask = MASK4((uint8_t)16);
        else if (address < IP(0xE0000000))
            mask = MASK4((uint8_t)24);
        else
            throw "Non-classful address.";
    }
}