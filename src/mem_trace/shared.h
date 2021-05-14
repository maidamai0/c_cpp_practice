#pragma once

#include <string>

class SharedLib {
public:
  SharedLib() = default;
  ~SharedLib() = default;

  void Print();

private:
  std::string s_;
  double d_ = 0.0;
  int a_ = 0;
};