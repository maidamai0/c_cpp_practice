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
#include <queue>

template <typename T>
class PCQueue {
 public:
  using value_type = T;

  auto Pop() -> value_type {
    std::unique_lock<std::mutex> lock{mtx_};
    cv_.wait(lock, [this] { return !data_.empty(); });
    const auto v = data_.front();
    data_.pop();
    return v;
  }

  void Push(value_type v) {
    {
      std::unique_lock<std::mutex> lock{mtx_};
      data_.push(v);
    }
    cv_.notify_one();
  }

 private:
  std::queue<value_type> data_;
  std::condition_variable cv_;
  std::mutex mtx_;
};
