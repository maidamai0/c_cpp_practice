#include "doctest/doctest.h"
#include "fmt/format.h"
#include "producer_consumer_queue.hpp"

#include <atomic>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <thread>
#include <utility>

template <typename... Args>
auto print(Args&&... args) {
  fmt::print(std::forward<Args>(args)...);
  std::fflush(stdout);
}

PCQueue<int> queue;
std::atomic_bool quit = false;

int64_t sum_produce = 0;
int64_t sum_consume = 0;

auto consumer() {
  while (!quit) {
    const auto v = queue.Pop();
    // print("consume: {}\n", v);
    sum_consume += v;
  }
}

auto producer() {
  for (int i = 0; i < 100'000; ++i) {
    queue.Push(i);
    sum_produce += i;
  }
}

TEST_CASE("int") {
  auto c = std::thread(consumer);
  auto p = std::thread(producer);
  p.join();

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(5s);
  print("sum_produce is {}, sum_consumer is {}\n", sum_produce, sum_consume);
  c.detach();
  CHECK(sum_produce == sum_consume);
}
