#pragma once

/**
 * @file trace.hpp
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   simple trace functions
 * @version 0.1
 * @date 2021-06-23
 *
 *
 */

#include <iostream>
#include <string_view>

struct fun_trace {
  fun_trace(std::string_view name) : name_{name} {
    local_count_ = count_++;
    std::cout << local_count_ << std::string(ident_, ' ') << ">>>> " << name_
              << '\n';
    ident_ += 4;
  }

  ~fun_trace() {
    ident_ -= 4;
    std::cout << local_count_ << std::string(ident_, ' ') << "<<<< " << name_
              << '\n';
  }

  std::string_view name_;
  size_t local_count_ = 0;
  thread_local static size_t ident_;
  thread_local static size_t count_;
};

thread_local size_t fun_trace::ident_ = 0;
thread_local size_t fun_trace::count_ = 0;

#define trace fun_trace _trace(__FUNCTION__)