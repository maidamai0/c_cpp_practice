#include <chrono>
#include <future>
#include <string>
#include <thread>

#include "common/stopwatch.h"
#include "doctest/doctest.h"
#include "fmt/format.h"

constexpr auto operator""_s(size_t seconds) -> std::chrono::seconds {
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

  ~print_guard() { fmt::print("leave {}\n", message_); }

 private:
  const std::string message_;
};

#define PG print_guard pg(__FUNCTION__);

auto sleep_for_1_second() {
  PG;
  sleep(1_s);
  return fmt::format("message from {}()", __FUNCTION__);
}

// block caller thread when future is destructed
auto future() {
  PG;
  auto future = std::async(std::launch::async, sleep_for_1_second);
}

// std::future will call wait before destrcuted
auto destruct_future() {
  PG;
  {
    print_guard pg("destruct_future block");
    auto future = std::async(std::launch::async, sleep_for_1_second);
  }
}

// destructor will call wait and block caller thread
auto discard_future() {
  PG;
  std::async(std::launch::async, sleep_for_1_second);
}

// wait will block caller thread
auto wait_future() {
  PG;
  auto future = std::async(std::launch::async, sleep_for_1_second);
  future.wait();
}

// get fill block caller thread
auto get_future() {
  PG;
  auto future = std::async(std::launch::async, sleep_for_1_second);
  fmt::print("{}\n", future.get());
}

// get fill block caller thread
auto pass_future(std::future<std::string> f) {
  PG;
  fmt::print("{}\n", f.get());
}

auto return_void_future() {
  print_guard guard(__FUNCTION__);
  return std::async(std::launch::async, sleep_for_1_second);
}

TEST_CASE("std async usage") {
  spdlog::stopwatch watch;
  future();
  CHECK(watch.elapsed().count() > 1);

  destruct_future();
  CHECK(watch.elapsed().count() > 1);

  discard_future();
  CHECK(watch.elapsed().count() > 1);

  wait_future();
  CHECK(watch.elapsed().count() > 1);

  get_future();
  CHECK(watch.elapsed().count() > 1);

  pass_future(std::async(std::launch::async, sleep_for_1_second));
  CHECK(watch.elapsed().count() > 1);

  auto ft = return_void_future();
  ft.get();
  CHECK(watch.elapsed().count() > 1);
}