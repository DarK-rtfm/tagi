#include "../include/ip.hh"
#include "../include/subnetgen.hh"
#include <vector>
namespace tools
{
    subnetgen::subnetgen(ip::net4 _pool, std::vector<ip::mask4> _masks) : pool(0)
    {
        pool = _pool;
        masks = _masks;
    }
    subnetgen::subnetgen(ip::net4 _pool, std::vector<uint32_t> _requirements) : pool(0)
    {
        pool = _pool;
        masks = {};
        for (auto req : _requirements)
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
            masks.push_back(ip::mask4(cidr));
        }
    }

    //! TODO
    subnetgen::subnetgen(ip::addr4 _pooladdr, std::vector<ip::mask4> _masks) : pool(0) {}
    subnetgen::subnetgen(ip::addr4 _pooladdr, std::vector<uint32_t> _requirements) : pool(0) {}
    int validate() { return 0; }

    std::vector<ip::net4> subnetgen::generate()
    {
        ip::addr4 current = pool.getaddress();
        for (auto mask : masks)
        {
            subnets.push_back(ip::net4(current, mask));
            current = current + 1 + ~mask.toUInt32();
        }
        return subnets;
    }
}
