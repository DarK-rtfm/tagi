#ifndef __MASK_6_HH
#define __MASK_6_HH

#include "ip/base/mask_t.hpp"

namespace IP {
using MASK6 = MASK<__uint128_t>;

/// NOTE: ig this is useless?
// template <>
// MASK6::MASK(std::string str);

/// NOTE: ig this is useless?
// template <>
// std::string MASK6::toString(char _flags);
} // namespace IP

#endif
