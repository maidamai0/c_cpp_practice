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

int64_t sum_produce = 0;
int64_t sum_consume = 0;

auto consumer() {
  while (true) {
    const auto v = queue.Pop();
    if(v < 0) {
      break;
    }
    sum_consume += v;
  }
}

auto producer() {
  for (int i = 0; i < 100'000; ++i) {
    queue.Push(i);
    sum_produce += i;
  }
  queue.Push(-1);
}

TEST_CASE("int") {
  auto c = std::thread(consumer);
  auto p = std::thread(producer);
  p.join();
  c.join();

  fmt::print("sum_produce is {}, sum_consumer is {}\n", sum_produce,
             sum_consume);
  CHECK(sum_produce == sum_consume);
}
