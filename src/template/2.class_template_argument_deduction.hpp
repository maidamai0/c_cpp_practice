#pragma once

#include <string>
#include <utility>
#include <vector>

template <typename T>
class Stack {
 public:
  Stack() = default;
  Stack(T t) : elems{std::move(t)} {}

 private:
  std::vector<T> elems;
};

Stack(char const*)->Stack<std::string>;