#pragma once

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "fmt/format.h"
#include "notification_queue.hpp"

class task_system {
 public:
  using log_t = std::function<void(const std::string& message)>;

  task_system() : count_(std::thread::hardware_concurrency()), queues_(count_) {
    for (size_t i = 0; i < count_; ++i) {
      workers_.emplace_back([this, i]() { worker_thread(i); });
    }
  }

  ~task_system() {
    for (auto& queue : queues_) {
      queue.done();
    }

    for (auto& worker : workers_) {
      worker.join();
    }
  }

  void async(notification_queue::task_t&& task) {
    auto next_queue = current_queue_++;
    for (size_t i = 0; i != count_; ++i) {
      if (queues_[(next_queue + i) % count_].try_push(std::move(task))) {
        log_("task pushed to queue #" +
             std::to_string((next_queue + i) % count_));
        return;
      }
    }

    queues_[next_queue % count_].push(std::move(task));
    log_("task pushed to queue #" + std::to_string(next_queue % count_));
  }

 private:
  void worker_thread(size_t index) {
    while (true) {
      std::optional<notification_queue::task_t> task;
      size_t queue_index = index;
      auto log = std::string("worker #") + std::to_string(index) +
                 " got task from queue #";
      for (size_t i = 0; i != count_; ++i) {
        queue_index = (queue_index + i) % count_;
        task = queues_[queue_index].try_pop();
        if (task) {
          log_(log + std::to_string((index + i) % count_));
          break;
        }
      }

      if (!task) {
        task = queues_[index].pop();
        queue_index = index;
      }

      assert(task);
      if (!task.value()) {
        queues_[queue_index].done();
        break;
      }

      log_(log + std::to_string(index));
      task.value()();
    }

    log_("worker #" + std::to_string(index) + " finished");
  }

  size_t count_{std::thread::hardware_concurrency()};
  std::vector<std::thread> workers_;
  std::vector<notification_queue> queues_;
  std::atomic<std::size_t> current_queue_{0};

  log_t log_ = [](const std::string& message) { fmt::print("{}\n", message); };
};
