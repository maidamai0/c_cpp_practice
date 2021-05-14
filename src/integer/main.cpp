#include <iostream>
#include <limits>

auto main() -> int {
  char c = std::numeric_limits<char>::min();

  for (int i = 0; i < 300; ++i) {
    std::cout << "c is " << c << std::endl;
    ++c;
  }
  return 0;
}