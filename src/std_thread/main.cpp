#include <thread>

#include "fmt/format.h"

auto main(int argc, char** argv) -> int {
  fmt::print("hardware thread num: {}", std::thread::hardware_concurrency());
}