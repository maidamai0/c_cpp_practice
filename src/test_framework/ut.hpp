#pragma once

#include <cassert>
#include <exception>
#include <functional>
#include <iostream>
#include <string_view>
#include <vector>

namespace internal {

using unit_func_t = std::function<void()>;
struct test_case {
  std::string_view name;
  unit_func_t func;
};

inline auto& get_cases() {
  static std::vector<test_case> cases;
  return cases;
}

inline auto register_case(std::string_view name, unit_func_t&& func) {
  get_cases().push_back(test_case{name, func});
  return true;
}

inline int run_unit_test() {
  std::cout << "================unit test running======================\n";
  const auto size = get_cases().size();
  size_t failed = 0;
  size_t idx = 1;
  for (const auto& test : get_cases()) {
    std::cout << "run test case " << idx << "/" << size << ' ' << test.name << "...\n";
    try {
      test.func();
      std::cout << idx << "/" << size << ' ' << test.name << " passed\n";
    } catch (const std::exception& e) {
      std::cout << idx << "/" << size << ' ' << test.name << " failed: " << e.what() << '\n';
      ++failed;
    }
    ++idx;
  }

  std::cout << "================test case run summary==================\n";
  if (failed == 0) {
    std::cout << "all case(s) passed\n";
  } else {
    std::cout << failed << " case(s) failed\n";
  }

  std::cout << "================test case run complete=================\n";

  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

}  // namespace internal

#define TEST_CASE(name)                                                      \
  inline void name();                                                        \
  inline static auto register_##name = internal::register_case(#name, name); \
  inline void name()

#define CHECK(x)              \
  if (!(x)) {                 \
    throw std::exception(#x); \
  }

#ifdef UT_MAIN
int main(int argc, char** argv) {
  return internal::run_unit_test();
}
#endif