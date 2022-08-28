#include "ip/v4/ip.hpp"
#include "ip/base/ip_t.hpp"
#include <iomanip>

namespace IP
{
    template <>
    IP4::IP(std::string str)
    {
        std::stringstream stream(str);
        value = 0;
        for (auto i : {3, 2, 1, 0})
        {
            int n;
            stream >> n;
            value += (uint8_t)n << (8 * i);
            if (i)
                stream.ignore();
        }
    }

    template <>
    std::string IP4::toString(char _flags)
    {
        std::ostringstream str;
        if ((_flags & 3) == IP4_STR::DOTTED)
        {
            if (_flags & IP4_STR::FILL0)
                str << std::setfill('0');
            for (auto i : {3, 2, 1, 0})
            {
                if (_flags & IP4_STR::PAD)
                    str << std::setw(3);
                str << (value << ((3 - i) * 8) >> ((3 - i) * 8) >> (i * 8));
                if (i)
                    str << '.';
            }
        }
        else
        {
            switch (_flags & 3)
            {
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
}