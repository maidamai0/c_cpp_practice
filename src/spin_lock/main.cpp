#include <array>
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>

#include "doctest/doctest.h"

constexpr auto worker_num = 20;

/**
 * @brief simple spin lock meets BasicLockable(https://en.cppreference.com/w/cpp/named_req/BasicLockable)
 *
 */
class SpinLock final {
public:
  SpinLock() = default;
  ~SpinLock() = default;

  void lock() {
    while (lock_.test_and_set(std::memory_order_acquire)) {
      // sacrifice some performance to save power
      std::this_thread::yield();
    }
  }

  void unlock() {
    lock_.clear(std::memory_order_release);
  }

  SpinLock(const SpinLock&) = delete;
  SpinLock& operator=(const SpinLock&) = delete;

private:
  std::atomic_flag lock_ = ATOMIC_FLAG_INIT;
};

SpinLock lock;

void add(int& sum, const bool need_lock = false) {
  for (auto cnt = 0; cnt < worker_num; ++cnt) {
    if (need_lock) {
      std::lock_guard<SpinLock> guard(lock);
      ++sum;
    } else {
      ++sum;
    }

    std::this_thread::sleep_for(std::chrono::microseconds(1));
  }
}

TEST_CASE("no lock") {
  auto sum = 0;
  std::vector<std::thread> workers;

  workers.reserve(worker_num);
  for (auto i = 0; i < worker_num; ++i) {
    workers.emplace_back(std::thread([&sum] { add(sum); }));
  }

  for (auto& worker : workers) {
    worker.join();
  }

  CHECK(sum == worker_num * worker_num);
}

TEST_CASE("spin lock") {
  auto sum = 0;
  std::vector<std::thread> workers;

  workers.reserve(worker_num);
  for (auto i = 0; i < worker_num; ++i) {
    workers.emplace_back(std::thread([&sum] { add(sum, true); }));
  }

  for (auto& worker : workers) {
    worker.join();
  }

  CHECK(sum == worker_num * worker_num);
}
