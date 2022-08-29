
#include "tools/subnetgenv6.hh"
#include <vector>
namespace tools

{
template <>
subnetgen6::subnetgen(IP::NET6 _pool, const std::vector<__uint128_t> &_reqs)
    : pool(_pool) {
  /// calculate std::vector<MASK6> based on requirements.
}
} // namespace tools
