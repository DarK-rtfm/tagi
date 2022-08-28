#include "ip/v6/ip.hpp"
#include "ip/base/ip_t.hpp"
#include <iomanip>

namespace IP
{
    template <>
    IP6::IP(std::string str)
    {
    }

    template <>
    std::string IP6::toString(char _flags)
    {
        return "";
    }
}