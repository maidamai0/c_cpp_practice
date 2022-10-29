/**
 * @file main.cpp
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief compile time string hash
 * @details see
 *              https://stackoverflow.com/questions/2111667/compile-time-string-hashing/2112111#2112111
 *              https://stackoverflow.com/questions/37658794/integer-constant-overflow-warning-in-constexpr
 *      for detail
 * @version 0.1
 * @date 2020-06-03
 *
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

constexpr auto hashFnv1b(const char* s, unsigned int fnv1a_basis = 0x811c9dc5, unsigned int fnv1a_prime = 0x01000193)
    -> unsigned int {
  return *s == 0
             ? fnv1a_basis
             : hashFnv1b(s + 1,
                         static_cast<unsigned int>((fnv1a_basis ^ *s) * static_cast<unsigned long long>(fnv1a_prime)));
}

constexpr auto operator"" _cshash(const char* str, std::size_t len) {
  return hashFnv1b(str);
}

void test(std::string key_str) {
  const auto key = hashFnv1b(key_str.c_str());
  switch (key) {
    case "first"_cshash: {
      std::cout << "first" << std::endl;
      break;
    }
    case "second"_cshash: {
      std::cout << "second" << std::endl;
      break;
    }
    case "third"_cshash: {
      std::cout << "third" << std::endl;
      break;
    }
    case "fourth"_cshash: {
      std::cout << "fourth" << std::endl;
      break;
    }
    case "fsfsafsaf"_cshash:
    default: {
      std::cout << "default" << std::endl;
    }
  }
}

// used for side-effects

auto main() -> int {
  std::vector<std::string> ss{"first", "second", "third", "fourth"};
  for (const auto& s : ss) {
    test(s);
  }

  return 0;
}
