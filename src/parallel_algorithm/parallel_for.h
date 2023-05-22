#pragma once

#include <future>
#include <vector>



template <typename Func>
inline void parallel_for(size_t begin, size_t end, Func&& f) {
  size_t hardware_threads = std::thread::hardware_concurrency();
  const auto chunk = (end - begin) / hardware_threads;
  std::vector<std::future<void>> results;

  for (size_t i = 0; i < end; i += chunk) {
    results.emplace_back(std::async(
        std::launch::async,
        [f](size_t begin, size_t end) {
          while (begin < end) {
            f(begin++);
          }
        },
        i, std::min(chunk + i, end)));
  }
}
