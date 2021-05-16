#pragma once

#include <iostream>
#include <string_view>

class ScopeTrace {
 public:
  ScopeTrace(std::string_view function) : function_{function} {
    std::cout << "enter " << function_ << std::endl;
  }
  ~ScopeTrace() { std::cout << "leave " << function_ << std::endl; }

 private:
  std::string_view function_;
};

#define FUNC_TRACE [[maybe_unused]] ScopeTrace fd(__FUNCTION__)
#define TRACE(s) [[maybe_unused]] ScopeTrace trace(s)