#include "../include/ip.hh"
#include <iostream>
#include <string>

#define THEN_DIE || (exit(0), 0)

int help(char*);
int cidr(char*);

int main(int argc, char **argv) {
    if (argc == 3 && std::string(argv[1]) == "cidr") cidr(argv[2]) THEN_DIE;
    help(*argv);
    return 0;
}


int help(char *name) {
    std::cout << name << " command argument(s)" << std::endl;
    std::cout << "\tcommands:" << std::endl;
    std::cout << "\t\tcidr <0..32> -- convert /nn prefix to dotted form" << std::endl;
    return 0;
}

int cidr(char* val) {
    ip::mask4 m = ip::mask4((uint8_t) atoi(val));
    std::cout << "/" << val << " = " << m.display() << std::endl;
    return 0;
}
