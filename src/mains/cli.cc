#include "ip/ipv4.hh"
#include <iostream>
#include <ranges>
#include <format>
#include <vector>

void inspect(const std::string& arg) {
  if (arg.contains('/')) {return;}
  IP::IPv4 address(arg);
  std::cout << std::format(
          "{1: ^40}\n"
          "protocol:     {2}\n"
          "address type: {3}\n"
          "class:        {4}\n"
          "{0:-<40}\n"
          "{5: ^40}\n"
          "Decimal representation: {6}\n"
          "Hex representation:     0x{7}\n"
          "{0:-<40}\n"
          "{8: ^40}\n",

          "",
          "GENERIC",
          "IPv4",
          "TBD (NET | HOST | BROAD)",
          "ABC"[address.getClass()],
          "ADDRESS VALUE",
          address.toString(IP::IPfmt::Dotted),
          address.toString(IP::IPfmt::Hex),
          "NETWORK"
          );
}

// MASSIVE TODO: FUCKING COMMAND HANDLING PROPERLY AAAAAAA. @BALINT HELP ME
// ALSO ERROR HANDLING
// EEEEEEEEE
int main(int argc, char **argv) {
  std::vector<std::string> args;
  args.reserve(argc);
  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  if (args[1] == "inspect") { inspect(args[2]);
}
}
