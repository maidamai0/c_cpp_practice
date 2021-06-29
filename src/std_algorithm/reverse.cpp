#include <algorithm>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"

TEST_CASE("std::reverse") {
  std::vector<int> nums{1, 3, 5, 6, 3, 4, 5, 6, 3};
  fmt::print("original:\n{}\n", nums);

  std::reverse(nums.begin(), nums.end());
  fmt::print("reverse:\n{}\n", nums);
}