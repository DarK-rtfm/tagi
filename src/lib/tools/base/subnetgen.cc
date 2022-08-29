#include "tools/subnetgen.hh"
#include "exceptions.hh"

namespace tools {
template <typename T>
subnetgen<T>::subnetgen(IP::NET<T> _pool, const std::vector<IP::MASK<T>> &_masks)
    : pool(_pool), masks(_masks) {}

template <typename T>
subnetgen<T>::subnetgen(IP::NET<T> _pool, const std::vector<T> &_reqs) {
  throw E_NoSpec();
}
} // namespace tools
