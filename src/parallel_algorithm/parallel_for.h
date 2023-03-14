#pragma once

#include <algorithm>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "common/scope_timer.h"

template <typename Func>
void worker(size_t begin, size_t end, Func&& f, size_t chunk, size_t stride) {
  FUNC_TIMER;
  while (begin < end) {
    size_t local_end = begin + chunk;
    for (int i = 0; i < chunk; ++i) {
      reducer(begin + i);
    }
    begin += stride;
  }
}

template <typename Func>
void parallel_for(size_t begin, size_t end, Func&& f, size_t chunk = 1000) {
  size_t chunk_num = (end - begin + chunk - 1) / chunk;
  size_t hardware_threads = std::thread::hardware_concurrency();
  size_t worker_num = std::min(chunk_num, hardware_threads);

  std::cout << "worker num is " << worker_num << std::endl;

  std::vector<std::jthread> workers;
  const auto stride = chunk * worker_num;

  for (size_t i = 0; i < worker_num; ++i) {
    workers.emplace_back(worker<Func>, i * chunk, end, std::forward<Func&&>(f), chunk, stride);
  }
}