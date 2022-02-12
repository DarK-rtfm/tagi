#include "../include/ip.hh"
#include <sstream>
#include <cmath>

#include <iostream>

namespace ip
{

addr4::addr4(uint32_t raw) {
    value = raw;
}

addr4::addr4(std::string str) {
    std::stringstream s(str);
    value = 0;
    for (int i = 3; i >= 0; i--) {
        char _void;
        int octet;
        s >> octet;
        s >> _void;
        value += octet * (1 << 8*i);
    }
}

std::string addr4::strDD() {
    std::stringstream s;
    for (int i = 3; i >= 0; i--) {
        s << (value >> (i*8)) % 256;
        if (i) s << ".";
    }
    return s.str();
}

std::string addr4::strHEX() {
    std::stringstream s;
    s << "0x" << std::hex << value;
    return s.str();
}

addrtype addr4::type(mask4 m) {
    if (value % (~m.value+1) == 0) return NET;
    if (value % (~m.value+1) == 1) return BROAD;
    return HOST;
}

mask4::mask4(uint8_t prefix) {
    value = ~((uint32_t) 0) >> (32 - prefix) << (32 - prefix);
}

mask4::mask4(std::string str) {
    std::stringstream s(str);
    value = 0;
    for (int i = 3; i >= 0; i--) {
        char _void;
        int octet;
        s >> octet;
        s >> _void;
        value += octet * (1 << 8*i);
    }
}

std::string mask4::strDD() {
    std::stringstream s;
    for (int i = 3; i >= 0; i--) {
        s << (value >> (i*8)) % 256;
        if (i) s << ".";
    }
    return s.str();
}

std::string mask4::strHEX() {
    std::stringstream s;
    s << "0x" << std::hex << value;
    return s.str();
}

uint8_t mask4::cidr() {
    int32_t val = value;
    uint8_t _cidr = 0;
    do _cidr++; while (val <<= 1);
    return _cidr;
}

mask4::mask4(uint32_t raw) {
    value = raw;
}

net4::net4(addr4 aobj, mask4 mobj) {
    address = aobj;
    mask = mobj;
}

/*
 * Automatic mask based on IP Classes
 */
net4::net4(addr4 aobj) {
    address = aobj;

    uint8_t cidr;
    if (aobj.value < 0b10000000000000000000000000000000) cidr = 8;
    else if (aobj.value < 0b11000000000000000000000000000000) cidr = 16;
    else if (aobj.value < 0b11100000000000000000000000000000) cidr = 24;
    else cidr = 32;
    mask = mask4(cidr);
}

bool net4::contains(addr4 aobj) {
    return (mask.value & aobj.value) == address.value;
}

net4 net4::next() {
    return net4(addr4(address.value + ~mask.value + 1), mask);
}

net4 net4::minimize(int needed) {
    needed++;
    int m = 0;
    while (needed) (m++, needed >>= 1);
    return net4(address, mask4((uint8_t)(32-m)));
}

addrtype net4::type() {
    return address.type(mask.value);
}

addrtype net4::type(addr4 a) {
    return a.type(mask.value);
}

}
