#define UT_MAIN
#include "ut.hpp"

TEST_CASE(test_case1) {
  std::cout << __FUNCTION__ << '\n';
}

TEST_CASE(test_case2) {
  std::cout << __FUNCTION__ << '\n';
}

TEST_CASE(always_false) {
  std::cout << __FUNCTION__ << '\n';
  CHECK(false);
}

TEST_CASE(test_case3) {
  std::cout << __FUNCTION__ << '\n';
}

TEST_CASE(one_plus_two_is_four) {
  std::cout << __FUNCTION__ << '\n';
  CHECK(1 + 2 == 4);
}
