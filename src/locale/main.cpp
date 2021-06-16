#include <locale>

#include "fmt/format.h"

void named_locales() {
  std::locale global_loc;
  fmt::print("global locale is {}\n", global_loc.name());

  std::locale preferred_loc{};
  fmt::print("preferred locale is {}\n", preferred_loc.name());

  std::locale c_loc{"C"};
  fmt::print("C locale is {}\n", c_loc.name());

  std::locale classic_loc{std::locale::classic()};
  fmt::print("clasic locale is {}\n", classic_loc.name());
}

int main() {
  named_locales();
}