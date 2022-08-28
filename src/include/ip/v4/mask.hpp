#ifndef __MASK_4_HH
#define __MASK_4_HH

#include "ip/base/mask_t.hpp"

namespace IP
{
    using MASK4 = MASK<uint32_t>;

    template <>
    MASK4::MASK(std::string str);

    template <>
    std::string MASK4::toString(char _flags);
}

#endif