#include <cstdint>
#include <string>

//TODO: refactor into sep. hh
typedef unsigned __int128 uint128_t;


namespace ip
{ 

class addr4 {
    public:
        uint32_t value;

        addr4() {value = 0;} // do not use directly
        addr4(uint32_t);
        addr4(std::string);
        std::string display();
};

class mask4 {
    public:
        uint32_t value;

        mask4() {value = 0;} // do not use directly
        mask4(uint32_t);
        mask4(uint8_t);
        mask4(std::string);
        std::string display();
};

class net4 {
    public:
        addr4 address;
        mask4 mask;

        net4(uint32_t addr4, uint8_t prefix);
        net4(addr4, mask4);
        net4(addr4);
        net4(std::string addr4, std::string mask4);

        bool contains(addr4 address);
        void next();
        void minimize(int needed);

        std::string display();
};

class addr6 {
    protected:
        uint128_t value;
    public:
        addr6(uint128_t value);
        addr6(std::string value);
        std::string display();
};

class net6 : addr6 {
    private:
        uint8_t prefix;
    public:
        net6(uint128_t addr6, uint8_t prefix);
        net6(std::string addr6, uint8_t prefix);
        net6(std::string);
        net6(addr4);

        bool containts(addr6 address);
        net6 next();
        net6 minimize(long needed);

        std::string display();
};

}
