#include "tools/subnetgenv4.hh"
#include <vector>
namespace tools {
template <>
subnetgen4::subnetgen(IP::NET4 _pool, const std::vector<uint32_t> &_reqs)
    : pool(_pool), masks({}) {

  for (auto req : _reqs) {
    //: TODO: refactor into separate method.
    uint8_t cidr = 32;
    --req;
    if (req <= 1) { //: NOTE: special case for 32 and 31 masks.
      cidr -= req;
    } else {
      do {
        --cidr;
      } while ((req >>= 1) != 0);
    }
    masks.push_back(IP::MASK4(cidr));
  };
}
} // namespace tools
