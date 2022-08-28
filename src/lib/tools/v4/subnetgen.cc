#include "tools/subnetgenv4.hh"
#include "exceptions.hh"
#include "ip/v4/net.hpp"
#include "ip/v4/mask.hpp"
#include "ip/v4/ip.hpp"
#include <vector>
namespace tools
{
    template class subnetgen<uint32_t>;

    template <>
    subnetgen4::subnetgen(IP::NET4 _p, std::vector<uint32_t> _reqs) : pool(IP::IP4(0), IP::MASK4((uint8_t)0))
    {
        pool = _p;
        masks = {};
        for (auto req : _reqs)
        {
            //: TODO: refactor into separate method.
            uint8_t cidr = 32;
            --req;
            if (req <= 1) //: NOTE: special case for 32 and 31 masks.
                cidr -= req;
            else
            {
                do
                    --cidr;
                while (req >>= 1);
            }
            masks.push_back(IP::MASK4(cidr));
        };
    }
}