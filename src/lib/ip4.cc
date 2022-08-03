#include "../include/ip.hh"
#include <cstdint>
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
        for (int i = 4; i --> 0;) {
            char _void;
            int octet;
            s >> octet;
            s >> _void;
            value.parts[i] = octet;
        }
    }

    addr4::addr4(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) {
        value.parts[0] = p4;
        value.parts[1] = p3;
        value.parts[2] = p2;
        value.parts[3] = p1;
    }

    uint32_t addr4::toUInt32() {return value.full;}

    std::string addr4::toString() {
        std::ostringstream str;
        for (auto i : {3, 2, 1, 0}) {
            str << (int)value.parts[i];
            if (i) str << '.';
        }
        return str.str();
    }

    bool addr4::operator<(addr4 other) {
        return value.full < other.toUInt32();
    }

    bool addr4::operator>(addr4 other) {
        return value.full > other.toUInt32();
    }

    bool addr4::operator==(addr4 other) {
        return value.full == other.toUInt32();
    }

    addr4 addr4::operator+(int size) {
        return addr4(value.full+size);
    }

    // TODO: Mask validation AND/OR proper exception handling without memory leek.
    mask4::mask4(uint32_t raw) : addr4(raw){ }
    mask4::mask4(std::string str) : addr4(str){ }

    mask4::mask4(uint8_t prefix) : addr4(0) {
        value = ~((uint32_t) 0) >> (32 - prefix) << (32 - prefix);
    }


    uint8_t mask4::toCIDR() {
        int32_t val = value.full;
        uint8_t _cidr = 0;
        do _cidr++; while (val <<= 1);
        return _cidr;
    }


    net4::net4(addr4 aobj, mask4 mobj) : address(aobj), mask(mobj) {
    }

    /*
     * Automatic mask based on IP Classes
     */
    net4::net4(addr4 aobj) : address(aobj) {
        uint8_t cidr;
        if (aobj < addr4(128, 0, 0, 0)) cidr = 8;
        else if (aobj < addr4(192, 0, 0, 0)) cidr = 16;
        else if (aobj < addr4(224, 0, 0, 0)) cidr = 24;
        else cidr = 32;
        mask = mask4(cidr);
    }

    bool net4::contains(addr4 aobj) {
        return (mask.toUInt32() & aobj.toUInt32()) == address.toUInt32();
    }

    addr4 net4::getaddress() {return address;}
    mask4 net4::getmask() {return mask;}

}
