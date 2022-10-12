#pragma once

#include <cassert>
#include <deque>
#include <functional>
#include <mutex>
#include <optional>
#include <queue>

class notification_queue {
 public:
  using lock_t = std::unique_lock<std::mutex>;
  using task_t = std::function<void()>;
  notification_queue() = default;

  void push(task_t&& task) {
    lock_t lock(mtx_);
    tasks_.emplace_back(std::move(task));
    ready_.notify_one();
  }

  auto try_push(task_t&& task) {
    lock_t lock(mtx_, std::try_to_lock);
    if (lock) {
      tasks_.emplace_back(std::move(task));
      ready_.notify_one();
      return true;
    }
    return false;
  }

  task_t pop() {
    lock_t lock(mtx_);
    while (tasks_.empty()) {
      ready_.wait(lock);
    }

    auto task = std::move(tasks_.front());
    tasks_.pop_front();
    return task;
  }

  auto try_pop() -> std::optional<task_t> {
    lock_t lock(mtx_, std::try_to_lock);
    if (!lock || tasks_.empty()) {
      return std::nullopt;
    }

    if (!tasks_.empty()) {
      auto task = std::make_optional(std::move(tasks_.front()));
      tasks_.pop_front();
      return task;
    }

    return std::nullopt;
  }

  auto done() {
    lock_t lock(mtx_);
    tasks_.emplace_back(nullptr);
  }

 private:
  std::mutex mtx_;
  std::condition_variable ready_;
  std::deque<task_t> tasks_;
};