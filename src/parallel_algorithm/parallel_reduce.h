#pragma once

#include <functional>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "common/scope_timer.h"
#include "fmt/core.h"

struct split {};

template <typename Reducer>
void do_reduce(size_t begin, size_t end, Reducer& reducer, size_t chunk, size_t stride) {
  FUNC_TIMER;
  while (begin < end) {
    size_t local_end = begin + chunk;
    for (int i = 0; i < chunk; ++i) {
      reducer(begin + i);
    }
    begin += stride;
  }
}

template <typename Reducer>
void parallel_reduce(size_t begin, size_t end, Reducer& reducer, size_t chunk = 1000) {
  size_t chunk_num = (end - begin + chunk - 1) / chunk;
  size_t hardware_threads = std::thread::hardware_concurrency();
  size_t worker_num = std::min(chunk_num, hardware_threads);

  std::cout << "worker num is " << worker_num << std::endl;

  std::vector<std::jthread> workers;
  workers.reserve(worker_num);

  std::vector<Reducer> reducers(worker_num);

  const auto stride = chunk * worker_num;

  for (size_t i = 0; i < worker_num; ++i) {
    reducers[i] = Reducer(reducer, split{});
    auto begin = i * chunk;
    workers.emplace_back(do_reduce<Reducer>, begin, end, std::ref(reducers[i]), chunk, stride);
  }

  for (auto& worker : workers) {
    worker.join();
  }

  for (const auto& splited_reducer : reducers) {
    reducer.merge(splited_reducer);
  }
};