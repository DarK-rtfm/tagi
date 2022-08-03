#include "ip.hh"
#include <iterator>
#include <vector>

namespace ip {
    //* should be enough to for-range
    class vlsm {
        private:
            addr4 address;
            std::vector<mask4> masks;
        public:
            net4& operator*() const;

            net4* operator++();

            net4 begin();
            net4 end() {return net4(addr4(0), mask4((uint8_t)0));};
    };
}
