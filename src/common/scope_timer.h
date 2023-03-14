#pragma once

#include <string_view>

#include "common/stopwatch.h"
#include "fmt/core.h"

class ScopeTimer {
 public:
  ScopeTimer(std::string_view name) : name_(name){};
  ~ScopeTimer() { fmt::print("{} cost {}\n", name_, watch_); }

 private:
  spdlog::stopwatch watch_;
  const std::string_view name_;
};

#define TIMER(x) ScopeTimer __timer(x)
#define FUNC_TIMER TIMER(__FUNCTION__)