#include "ip.hh"
#include <vector>

namespace tools
{
    class subnetgen
    {
    private:
        ip::net4 pool;
        std::vector<ip::mask4> masks;
        std::vector<ip::net4> subnets;

    public:
        subnetgen(ip::net4 _pool, std::vector<ip::mask4> _masks);
        subnetgen(ip::net4 _pool, std::vector<uint32_t> _requirements);
        subnetgen(ip::addr4 _pooladdr, std::vector<ip::mask4> _masks);
        subnetgen(ip::addr4 _pooladdr, std::vector<uint32_t> _requirements);
        int validate();
        std::vector<ip::net4> generate();
    };
}
