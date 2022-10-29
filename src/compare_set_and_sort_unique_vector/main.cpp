#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include <vector>

#include "common/stopwatch.h"

static constexpr size_t max = 100000;
static constexpr size_t max_count = 3000;
static constexpr size_t test_count = 10;

void test() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<size_t> start(0, max);
  std::uniform_int_distribution<size_t> count(100, max_count);

  std::vector<size_t> start_values;
  std::vector<size_t> cnts;

  for (size_t i = 0; i < test_count; ++i) {
    start_values.push_back(start(mt));
    cnts.push_back(count(mt));
  }

  spdlog::stopwatch watch;
  {
    std::vector<size_t> sort_unique_vector;
    // vector with sort and unique
    for (size_t i = 0; i < start_values.size(); ++i) {
      const auto cnt = cnts[i];
      auto start_value = start_values[i];

      for (size_t i = 0; i < cnt; ++i) {
        sort_unique_vector.push_back(start_value++);
      }

      std::sort(sort_unique_vector.begin(), sort_unique_vector.end());
      sort_unique_vector.erase(std::unique(sort_unique_vector.begin(), sort_unique_vector.end()),
                               sort_unique_vector.end());
    }
    fmt::print("vector size is {}\n", sort_unique_vector.size());
    fmt::print("elapsed: {} seconds\n", watch);
  }

  {
    std::set<size_t> set;
    // set
    for (size_t i = 0; i < start_values.size(); ++i) {
      const auto cnt = cnts[i];
      auto start_value = start_values[i];

      for (size_t i = 0; i < cnt; ++i) {
        set.insert(start_value++);
      }
    }

    fmt::print("set size is {}\n", set.size());
    fmt::print("elapsed: {} seconds\n", watch);
  }
}

auto main(int argc, char** argv) -> int {
  test();
}