#include "ip/v4/mask.hpp"
#include "ip/base/mask_t.hpp"
#include "sstream"

namespace IP
{

    template <>
    MASK4::MASK(std::string str)
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
    std::string MASK4::toString(char _flags)
    {
        std::ostringstream str;
        for (auto i : {3, 2, 1, 0})
        {
            str << (getBitmask() << ((3 - i) * 8) >> ((3 - i) * 8) >> (i * 8));
            if (i)
                str << '.';
        }
        return str.str();
    }
}