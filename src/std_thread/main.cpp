#include "fmt/format.h"
#include <thread>

auto main(int argc, char** argv) -> int {
  fmt::print("hardware thread num: {}", std::thread::hardware_concurrency());
}