#include "../include/ip.hh"
#include "../include/subnetgen.hh"
#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include <vector>

// MASSIVE TODO: FUCKING COMMAND HANDLING PROPERLY AAAAAAA. @BALINT HELP ME
// ALSO ERROR HANDLING
// EEEEEEEEE
#define THEN_DIE > 1 || (exit(0), 0)

int help(char *);
int cidr(char **);
int subnet(char **);

int main(int argc, char **argv)
{
    if (argc == 3 && std::string(argv[1]) == "cidr")
        cidr(argv + 2) THEN_DIE;
    if (argc >= 4 && std::string(argv[1]) == "vlsm")
        subnet(argv + 2) THEN_DIE;
    help(*argv);
    return 0;
}

int help(char *name)
{
    std::cout << name << " command argument(s)" << std::endl;
    std::cout << "\tcommands:" << std::endl;
    std::cout << "\t\tcidr <0..32> -- convert /nn prefix to dotted form" << std::endl;
    std::cout << "\t\tvlsm <a.b.c.d> <1..> ... -- subnet without wasting as much as possible" << std::endl;
    return 0;
}

int cidr(char **val)
{
    std::stringstream s(*val);
    int nn;
    s >> nn;

    ip::mask4 m((uint8_t)nn);
    std::cout << *val << ": " << m.toString() << std::endl;
    return 0;
}

int subnet(char **args)
{
    ip::net4 pool(ip::addr4(*args++));
    std::vector<uint32_t> reqs({});
    do
        reqs.push_back(std::stoi(*args));
    while (*++args);

    tools::subnetgen g(pool, reqs);
    auto subnets = g.generate();
    for (auto subnet : subnets)
    {
        std::cout << subnet.getaddress().toString() << "/" << (int)subnet.getmask().toCIDR() << "\n";
    }
    std::cout << std::flush;
    return 0;
}
