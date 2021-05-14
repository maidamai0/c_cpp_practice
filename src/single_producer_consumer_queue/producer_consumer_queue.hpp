#pragma once

/**
 * @file producer_consumer_queue.hpp
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-08-26
 *
 * @copyright Copyright (c) 2020 All Rights Reserved
 *
 */

#include <condition_variable>
#include <mutex>
#include <vector>

template <typename T>
class PCQueue {
public:
  using value_type = T;

  auto Pop() -> value_type {
    std::unique_lock<std::mutex> lock{mtx_};
    while (data_.empty()) {
      cv_.wait(lock);
    }
    const auto v = data_.back();
    data_.pop_back();
    return v;
  }

  void Push(value_type v) {
    {
      std::unique_lock<std::mutex> lock{mtx_};
      data_.push_back(v);
    }
    cv_.notify_one();
  }

private:
  std::vector<value_type> data_;
  std::condition_variable cv_;
  std::mutex mtx_;
};