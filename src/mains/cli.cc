#include "tools/subnetgenv4.hh"
#include <iostream>
#include <ranges>
#include <vector>

// MASSIVE TODO: FUCKING COMMAND HANDLING PROPERLY AAAAAAA. @BALINT HELP ME
// ALSO ERROR HANDLING
// EEEEEEEEE
#define BRANCH_COMMANDS() int status = -1;
#define COMMAND(name)                                                          \
  if (status == -1 && args[1] == #name)                                        \
    status = name(args);
#define FALLBACK(name)                                                         \
  if (status == -1)                                                            \
    status = name(args);
#define ONERROR(name)                                                          \
  if (status > 0)                                                              \
    name(args);
#define CHECK(X)                                                               \
  if (!(X))                                                                    \
    return 1;

typedef std::vector<std::string> args_t;

int help(const args_t &args);
int cidr(const args_t &args);
int subnet(const args_t& args);

int main(int argc, char **argv) {
  args_t args({});
  do {
    args.push_back(std::string(*argv));
  } while (*++argv != nullptr);

  BRANCH_COMMANDS();
  COMMAND(cidr);
  COMMAND(subnet);
  FALLBACK(help);
  ONERROR(help);
  return status;
}

int help(const args_t &args) {
  std::cout << args[0] << " command argument(s)" << std::endl;
  std::cout << "\tcommands:" << std::endl;
  std::cout << "\t\tcidr <0..32> -- convert /nn prefix to dotted form"
            << std::endl;
  std::cout << "\t\tsubnet <a.b.c.d> <1..> ... -- subnet without wasting as "
               "much as possible"
            << std::endl;
  return 0;
}

int cidr(const args_t &args) {
  CHECK(args.size() > 2);
  int cidr = std::stoi(args[2]);

  IP::MASK4 mask((uint8_t)cidr);
  std::cout << args[2] << ": " << mask.toString() << std::endl;
  return 0;
}

int subnet(const args_t& args) {
  CHECK(args.size() > 3)
  IP::NET4 pool = IP::NET4(IP::IP4(args[2]));

  std::vector<uint32_t> reqs({});
  // waiting for libc++ to give out ranges...
  for (const auto& arg : args | std::views::drop(3)) {
    reqs.push_back(std::stoi(arg));
  }

  tools::subnetgen generator(pool, reqs);
  auto subnets = generator.generate();
  for (auto subnet : subnets) {
    std::cout << subnet.getAddress().toString(IP::IP4_STR::PAD) << "/"
              << (int)subnet.getMask().getValue() << "\n";
  }
  std::cout << std::flush;
  return 0;
}
