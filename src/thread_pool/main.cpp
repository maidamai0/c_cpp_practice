#include <atomic>
#include <cassert>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadPool {
  using task_type = std::function<void()>;

public:
  ThreadPool(size_t num = std::thread::hardware_concurrency()) {
    for (size_t i = 0; i < num; ++i) {
      workers_.emplace_back(std::thread([this] {
        while (true) {
          task_type task;
          {
            std::unique_lock<std::mutex> lock(task_mutex_);
            task_cond_.wait(lock, [this] { return !tasks_.empty(); });
            task = std::move(tasks_.front());
            tasks_.pop();
          }
          if (!task) {
            std::cout << "worker #" << std::this_thread::get_id() << " exited" << std::endl;
            push_stop_task();
            return;
          }
          task();
        }
      }));
      std::cout << "worker #" << workers_.back().get_id() << " started" << std::endl;
    }
  }

  ~ThreadPool() {
    Stop();
  }

  void Stop() {
    push_stop_task();
    for (auto& worker : workers_) {
      if (worker.joinable()) {
        worker.join();
      }
    }

    // clear all pending tasks
    std::queue<task_type> empty{};
    std::swap(tasks_, empty);
  }

  template <typename F, typename... Args>
  auto Push(F&& f, Args&&... args) {
    using return_type = std::invoke_result_t<F, Args...>;
    auto task
      = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    auto res = task->get_future();

    {
      std::lock_guard<std::mutex> lock(task_mutex_);
      tasks_.emplace([task] { (*task)(); });
    }
    task_cond_.notify_one();

    return res;
  }

private:
  void push_stop_task() {
    std::lock_guard<std::mutex> lock(task_mutex_);
    tasks_.push(task_type{});
    task_cond_.notify_one();
  }

  std::vector<std::thread> workers_;
  std::queue<task_type> tasks_;
  std::mutex task_mutex_;
  std::condition_variable task_cond_;
};

auto main(int argc, char** argv) -> int {
  ThreadPool pool;
  const auto start = std::chrono::steady_clock::now();

  auto ret = pool.Push(
    [](int sec) {
      std::this_thread::sleep_for(std::chrono::seconds(sec));
      std::cout << "completed in worker #" << std::this_thread::get_id() << std::endl;
      return 1;
    },
    2);

  auto ret2 = pool.Push(
    [](std::chrono::seconds sec) {
      std::this_thread::sleep_for(sec);
      std::cout << "completed in worker #" << std::this_thread::get_id() << std::endl;
      return 2;
    },
    std::chrono::seconds(1));

  auto hello = pool.Push(
    [](std::string&& message) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1s);
      std::cout << "completed in worker #" << std::this_thread::get_id() << std::endl;
      return "hello " + message;
    },
    "world");

  auto sum = pool.Push(
    [](int x, int y, int z) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1s);
      std::cout << "completed in worker #" << std::this_thread::get_id() << std::endl;
      return x + y + z;
    },
    1, 2, 3);

  auto no_args = pool.Push([]() {
    std::cout << "completed in worker #" << std::this_thread::get_id()
              << ", No args" << std::endl;
  });

  assert(ret.get() == 1);
  assert(ret2.get() == 2);
  assert(hello.get() == "hello world");
  assert(sum.get() == 6);
  no_args.get();

  const auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start);
  std::cout << elapsed.count() << " seconds elapsed" << std::endl;

  return 0;
}