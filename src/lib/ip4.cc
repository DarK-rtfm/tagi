#include "../include/ip.hh"
#include <sstream>
#include <cmath>

#include <iostream>

namespace ip{

addr4::addr4(uint32_t raw) {
    value = raw;
}

addr4::addr4(std::string str) {
    std::stringstream s(str);
    value = 0;
    for (int i = 3; i >= 0; i--) {
        uint8_t octet;
        s >> octet;
        value += octet * pow(2, 8*i);
    }
}

std::string addr4::display() {
    std::stringstream s;
    for (int i = 3; i >= 0; i--) {
        s << (value >> (i*8)) % 256;
        if (i) s << ".";
    }
    return s.str();
}

mask4::mask4(uint8_t prefix) {
    value = ~((uint32_t) 0) >> (32 - prefix) << (32 - prefix);
}

mask4::mask4(std::string str) {
    std::stringstream s(str);
    value = 0;
    for (int i = 3; i >= 0; i--) {
        uint8_t octet;
        s >> octet;
        value += octet * pow(2, 8*i);
    }
}

std::string mask4::display() {
    std::stringstream s;
    for (int i = 3; i >= 0; i--) {
        s << (value >> (i*8)) % 256;
        if (i) s << ".";
    }
    return s.str();
}

mask4::mask4(uint32_t raw) {
    value = raw;
}

net4::net4(uint32_t raw, uint8_t cidr) {
    address = addr4(raw);
    mask = mask4(cidr);
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
    else throw ("excuse me why tf would you net4 with non-useable nets");
    mask = mask4(cidr);
}

net4::net4(std::string astr, std::string mstr) {
    address = addr4(astr);
    mask = mask4(mstr);
}

bool net4::contains(addr4 aobj) {
    return (mask.value && aobj.value) == address.value;
}

void net4::next() {
    address.value += ~mask.value + 1;
}

void net4::minimize(int needed) {
    // mask = mask(MSB);
}

}
