#include "tools/subnetgen.hh"
#include "exceptions.hh"

namespace tools
{
    template <typename T>
    subnetgen<T>::subnetgen(IP::NET<T> _p, std::vector<IP::MASK<T>> _ms)
    {
        pool = _p;
        masks = _ms;
    }

    template <typename T>
    subnetgen<T>::subnetgen(IP::NET<T> _p, std::vector<T> _reqs)
    {
        throw E_NoSpec();
    }
}