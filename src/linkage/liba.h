#pragma once

#include <iostream>
#include <string>

#include "fmt/format.h"

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

template <typename T>
void foo(T a) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <>
inline void foo(float specilize_float) {
  std::cout << __PRETTY_FUNCTION__ << "specilize_float" << std::endl;
}