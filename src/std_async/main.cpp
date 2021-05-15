#include <chrono>
#include <future>
#include <string>
#include <thread>

#include "fmt/format.h"

constexpr auto operator""_s(unsigned long long seconds) -> std::chrono::seconds {
  return std::chrono::seconds(seconds);
}

auto sleep(const std::chrono::seconds secs) -> void {
  return std::this_thread::sleep_for(secs);
}

class print_guard {
public:
  print_guard(std::string&& message) : message_(message) {
    fmt::print("enter {}\n", message_);
  }

  ~print_guard() {
    fmt::print("leave {}\n", message_);
  }

private:
  const std::string message_;
};

auto sleep_for_1_second() {
  sleep(1_s);
  fmt::print("leave {}\n", __FUNCTION__);
  return fmt::format("message from {}()", __FUNCTION__);
}

// block caller thread when future is destructed
auto future() {
  fmt::print("enter {}\n", __FUNCTION__);
  auto future = std::async(std::launch::async, sleep_for_1_second);
  fmt::print("leave {}\n", __FUNCTION__);
}

// std::future will call wait before destrcuted
auto destruct_future() {
  fmt::print("enter {}\n", __FUNCTION__);
  {
    fmt::print("enter block\n");
    auto future = std::async(std::launch::async, sleep_for_1_second);
    fmt::print("leave block\n");
  }
  fmt::print("leave {}\n", __FUNCTION__);
}

// destructor will call wait and block caller thread
auto discard_future() {
  fmt::print("enter {}\n", __FUNCTION__);
  std::async(std::launch::async, sleep_for_1_second);
  fmt::print("leave {}\n", __FUNCTION__);
}

// wait will block caller thread
auto wait_future() {
  fmt::print("enter {}\n", __FUNCTION__);
  auto future = std::async(std::launch::async, sleep_for_1_second);
  future.wait();
  fmt::print("leave {}\n", __FUNCTION__);
}

// get fill block caller thread
auto get_future() {
  fmt::print("enter {}\n", __FUNCTION__);
  auto future = std::async(std::launch::async, sleep_for_1_second);
  fmt::print("{}\n", future.get());
  fmt::print("leave {}\n", __FUNCTION__);
}

// get fill block caller thread
auto pass_future(std::future<std::string> f) {
  fmt::print("enter {}\n", __FUNCTION__);
  fmt::print("{}\n", f.get());
  fmt::print("leave {}\n", __FUNCTION__);
}

auto return_void_future() {
  print_guard guard(__FUNCTION__);
  return std::async(std::launch::async, sleep_for_1_second);
}

auto main(int argc, char** argv) -> int {
  const auto gap = []() {
    sleep(1_s);
    fmt::print("\n");
  };

  future();
  gap();

  destruct_future();
  gap();

  discard_future();
  gap();

  wait_future();
  gap();

  get_future();
  gap();

  pass_future(std::async(std::launch::async, sleep_for_1_second));
  gap();

  auto ft = return_void_future();
  ft.get();
  fmt::print("get from return_void_future\n");
  gap();

  std::getchar();
}
