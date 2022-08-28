#include "ip/base/net_t.hpp"
#include <vector>

namespace tools
{
    template <typename T>
    class subnetgen
    {
    private:
        IP::NET<T> pool;
        std::vector<IP::MASK<T>> masks;
        std::vector<IP::NET<T>> subnets;

    public:
        subnetgen(IP::NET<T> _pool, std::vector<IP::MASK<T>> _masks);
        subnetgen(IP::NET<T> _pool, std::vector<T> _reqs);
        int validate();
        std::vector<IP::NET<T>> generate();
    };

    template <typename T>
    std::vector<IP::NET<T>> subnetgen<T>::generate()
    {
        IP::IP<T> current = pool.getAddress();
        for (auto mask : masks)
        {
            subnets.push_back(IP::NET<T>(current, mask));
            current = current + 1 + ~mask.getBitmask();
        }
        return subnets;
    }
}