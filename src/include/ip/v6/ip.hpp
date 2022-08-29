#ifndef __IP_6_HH
#define __IP_6_HH

#include "ip/base/ip_t.hpp"

namespace IP {
using IP6 = IP<__uint128_t>;
enum IP6_STR { FULL = 0, SHORTENED = 1, SKIPPED = 2 };

template <> IP6::IP(const std::string & str);

template <> std::string IP6::toString(char _flags);
} // namespace IP

#endif
