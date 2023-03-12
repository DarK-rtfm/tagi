#ifndef __IP_4_HH
#define __IP_4_HH

#include <string>
#include <bitset>

namespace IP {


enum IPfmt {
    Dotted = 1,
    Hex = 2,
};

enum IPclass {
    A = 0,
    B = 1,
    C = 2,
    R = 3,
    O = 4,
};

class IPv4 {
    uint32_t address;

public:
    IPv4();
    IPv4(uint32_t);
    IPv4(const std::string &);
    
    std::string toString(IPfmt fmt = IPfmt::Hex);
    IPclass getClass();
};


}
#endif
