#include "../include/ip.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define THEN_DIE  > 1 || (exit(0), 0)

int help(char*);
int cidr(char*);
int subnet(char**);

int main(int argc, char **argv) {
    if (argc == 3 && std::string(argv[1]) == "cidr") cidr(argv[2]) THEN_DIE;
    if (argc >= 4 && std::string(argv[1]) == "vlsm") subnet(argv+2) THEN_DIE;
    help(*argv);
    return 0;
}


int help(char *name) {
    std::cout << name << " command argument(s)" << std::endl;
    std::cout << "\tcommands:" << std::endl;
    std::cout << "\t\tcidr <0..32> -- convert /nn prefix to dotted form" << std::endl;
    std::cout << "\t\tvlsm <a.b.c.d> <1..> ... -- subnet without wasting as much as possible" << std::endl;
    return 0;
}

int cidr(char* val) {
    ip::mask4 m = ip::mask4((uint8_t) atoi(val));
    std::cout << "/" << +m.cidr() << " = " << m.strDD() << std::endl;
    return 0;
}

int subnet(char** args) {
    ip::net4 main = ip::net4(ip::addr4(*args));
    if (main.type() != ip::NET) {
        std::cout << "This is a host address!" << std::endl;
        return 1;
    }
    std::stringstream serr;
    std::stringstream sout;
    //std::vector<ip::net4> subnets = {};
    

    sout << main.address.strDD() << "/" << +main.mask.cidr() << ":" << std::endl;
    ip::net4 temp = main.minimize(atoi(*++args));
    sout << "\t" << temp.address.strDD() << "/" << +temp.mask.cidr() << std::endl;
    while (*++args) {
        temp = temp.next().minimize(atoi(*args));
        if (!main.contains(temp.address)) serr << "W: Subnet " << temp.address.strDD() << " does not fit. Consider using larger address pool." << std::endl;
        if (temp.type() != ip::NET) serr << "WW: Subnet " << temp.address.strDD() << " " << temp.address.strHEX() << " does not align with mask. This WILL make it impossible to use. You SHOULD put the subnets in descreasing order based on requires hosts, or equvivalently, in increasing order based on mask values." << std::endl;
    sout << "\t" << temp.address.strDD() << "/" << +temp.mask.cidr() << std::endl;
    }
    std::cerr << serr.str();
    std::cout << sout.str();
    return 0;
}
