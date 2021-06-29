#include <algorithm>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"

TEST_CASE("rotate") {
  std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7};
  fmt::print("original:\n");
  fmt::print("{}\n", numbers);

  std::rotate(numbers.begin(), numbers.begin() + 3, numbers.end());
  fmt::print("rotate from 3:\n");
  fmt::print("{}\n", numbers);

  std::sort(numbers.begin(), numbers.end());
  fmt::print("reset:\n");
  fmt::print("{}\n", numbers);

  std::rotate(numbers.rbegin(), numbers.rbegin() + 2, numbers.rend());
  fmt::print("rotate from 7:\n");
  fmt::print("{}\n", numbers);
}
