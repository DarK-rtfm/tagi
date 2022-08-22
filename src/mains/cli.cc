#include "../include/ip.hh"
#include "../include/subnetgen.hh"
#include <iostream>
#include <vector>
#include <ranges>

// MASSIVE TODO: FUCKING COMMAND HANDLING PROPERLY AAAAAAA. @BALINT HELP ME
// ALSO ERROR HANDLING
// EEEEEEEEE
#define BRANCH_COMMANDS() int status = -1;
#define COMMAND(name) if (status == -1 && args[1] == #name) status = name(args);
#define FALLBACK(name) if (status == -1) status = name(args);
#define ONERROR(name) if (status > 0) name(args);
#define CHECK(X) if (!(X)) return 1;

typedef std::vector<std::string> args_t;

int help(const args_t args);
int cidr(const args_t args);
int subnet(const args_t args);

int main(int argc, char **argv)
{
    args_t args({});
    do
        args.push_back(std::string(*argv));
    while (*++argv);


    BRANCH_COMMANDS();
    COMMAND(cidr);
    COMMAND(subnet);
    FALLBACK(help);
    ONERROR(help);
    return status;
}

int help(const args_t args)
{
    std::cout << args[0] << " command argument(s)" << std::endl;
    std::cout << "\tcommands:" << std::endl;
    std::cout << "\t\tcidr <0..32> -- convert /nn prefix to dotted form" << std::endl;
    std::cout << "\t\tsubnet <a.b.c.d> <1..> ... -- subnet without wasting as much as possible" << std::endl;
    return 0;
}

int cidr(const args_t args)
{
    CHECK(args.size() > 2);
    int nn = std::stoi(args[2]);

    ip::mask4 m((uint8_t)nn);
    std::cout << args[2] << ": " << m.toString() << std::endl;
    return 0;
}

int subnet(const args_t args)
{
    CHECK(args.size() > 3)
    ip::net4 pool = ip::net4(ip::addr4(args[2]));

    std::vector<uint32_t> reqs({});
    for (auto arg : args | std::ranges::views::drop(3)) {
        reqs.push_back(std::stoi(arg));
    }

    tools::subnetgen g(pool, reqs);
    auto subnets = g.generate();
    for (auto subnet : subnets)
    {
        std::cout << subnet.getaddress().toString() << "/" << (int)subnet.getmask().toCIDR() << "\n";
    }
    std::cout << std::flush;
    return 0;
}
