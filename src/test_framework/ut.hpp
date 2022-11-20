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
  std::string_view file;
  int line;
  unit_func_t func;
  bool failed = false;
};

inline auto& get_cases() {
  static std::vector<test_case> cases;
  return cases;
}

inline auto register_case(std::string_view name, std::string_view file, int line, unit_func_t&& func) {
  get_cases().push_back(test_case{name, file, line, func});
  return true;
}

inline int run_unit_test() {
  std::cout << "================unit test running======================\n";
  const auto size = get_cases().size();
  size_t failed = 0;
  size_t idx = 1;
  for (auto& test : get_cases()) {
    std::cout << "\nrunning " << idx << "/" << size << ' ' << test.name << "...\n";
    try {
      test.func();
      std::cout << idx << "/" << size << ' ' << test.name << " passed\n";
    } catch (const std::exception& e) {
      test.failed = true;
      std::cerr << idx << "/" << size << ' ' << test.name << " failed\n";
      ++failed;
    }
    ++idx;
  }

  std::cout << "\n================test case run summary==================\n";
  if (failed == 0) {
    std::cout << "all case(s) passed\n";
  } else {
    std::cerr << failed << " case(s) failed:\n";
    const auto size = get_cases().size();
    size_t idx = 1;
    for (const auto& test : get_cases()) {
      if (test.failed) {
        std::cerr << "  " << idx << '/' << size << ' ' << test.name << " at " << test.file << ':' << test.line << '\n';
      }
      ++idx;
    }
  }

  std::cout << "\n================test case run complete=================\n";

  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

}  // namespace internal

#define TEST_CASE(name)                                                                          \
  inline void name();                                                                            \
  inline static auto register_##name = internal::register_case(#name, __FILE__, __LINE__, name); \
  inline void name()

#define CHECK(x)                                                                          \
  if (!(x)) {                                                                             \
    std::cerr << "CHECK failed: " << #x << " at " << __FILE__ << ':' << __LINE__ << '\n'; \
    throw std::runtime_error(#x);                                                         \
  }

#ifdef UT_MAIN
int main(int argc, char** argv) {
  return internal::run_unit_test();
}
#endif