#include <cstdint>
#include <string>

namespace ip {

    enum netclass {CLASSLESS, A, B, C};
    enum addrtype {NET, HOST, BROAD};


    class addr4 {
        protected:
            union u_addr{
                uint32_t full;
                uint8_t parts[4];
                void operator = (uint32_t val) {full = val;};
            } value;

        public:
            addr4(uint32_t);
            addr4(uint8_t,uint8_t,uint8_t,uint8_t);
            addr4(std::string);

            uint32_t toUInt32();
            std::string toString();
            bool operator < (addr4);
            bool operator > (addr4);
            bool operator == (addr4);
            addr4 operator + (int);
    };

    //  PROBLEM:
    //  different set of constructors needed for mask validation and CIDR notation.
    //  TODO: disallow use of addr4 constructors.
    class mask4 : public addr4 {
        public:
            mask4() : addr4(0) {}; // TODO: FUCKING PURGE THE DEF CONSTRUCTORS
            mask4(uint32_t);
            mask4(uint8_t, uint8_t, uint8_t, uint8_t);
            mask4(uint8_t);
            mask4(std::string);
            uint8_t toCIDR();
    };

    class net4 {
        private:
            addr4 address;
            mask4 mask;
        public:
            net4(addr4 netaddr, mask4 mask);
            net4(addr4 netaddr);

            addr4 getaddress();
            mask4 getmask();
            addr4 getwild(); // TODO: ??
            std::string toString();
            enum netclass netclass();
            enum addrtype addrtype(addr4);

            bool contains(addr4 address);
    };
}
