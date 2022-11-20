#include <algorithm>
#include <chrono>
#include <execution>
#include <random>
#include <thread>
#include <vector>

#include "common/stopwatch.h"
#include "doctest/doctest.h"
#include "fmt/format.h"

int add_int(int a, int b) {
  std::this_thread::sleep_for(std::chrono::nanoseconds(200));
  return a + b;
}

TEST_CASE("std::reduce") {
  std::random_device rd{};
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist{0, 1};

  std::vector<int> nums;
  std::generate_n(std::back_inserter(nums), 10'000, [&gen, &dist]() { return dist(gen); });

  spdlog::stopwatch watch;
  auto sum = std::reduce(nums.begin(), nums.end(), 0, add_int);
  fmt::print("reduce:           {}\n", watch);
  watch.reset();

  auto sum_parallel = std::reduce(std::execution::par, nums.begin(), nums.end(), 0, add_int);
  fmt::print("reduce parallel:  {}\n", watch);
  CHECK(sum == sum_parallel);

  // possible outputs:
  // reduce:           0.0748859
  // reduce parallel:  0.0084969
}
