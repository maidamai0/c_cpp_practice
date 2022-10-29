#include <array>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <vector>

template <typename T, size_t size>
auto operator<<(std::ostream& os, std::array<T, size> arr) -> std::ostream& {
  for (const auto e : arr) {
    os << e << " ";
  }
  os << std::endl;
  return os;
}

auto main(int argc, char** argv) -> int {
  // for (int i = 0; i < 1000; ++i) {
  std::array<char, 1000> dst;
  std::string s = "hello world";
  memcpy(dst.data(), s.c_str(), dst.size());  // is this undefined behavior?
  // }
}
