#pragma once

#include <iostream>
#include <type_traits>

template <typename Int, typename std::enable_if<std::is_signed<Int>::value, bool>::type = true>
auto to_unsigned(Int value) {
  std::cout << "signed\n";
}

template <typename Int, typename std::enable_if<std::is_unsigned<Int>::value, bool>::type = true>
auto to_unsigned(Int value) {
  std::cout << "unsigned\n";
}