#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

#include "common/scope_timer.h"
#include "parallel_algorithm/parallel_for.h"
#include "parallel_algorithm/parallel_reduce.h"

void test_parallel_for() {
  constexpr size_t size = 1'000'000'000;
  //   std::vector<int> numbers_serial(size);
  std::vector<int> numbers_para(size);
  std::vector<int> numbers_std_para(size);

  {
    TIMER("parallel_for");
    parallel_for(
        0, size, [&numbers_para](int i) { numbers_para[i] = i * 2; }, 100'000'000);
  }

  //   {
  //     TIMER("serial");
  //     for (int i = 0; i < size; ++i) {
  //       numbers_serial[i] = i * 2;
  //     }
  //   }

  {
    TIMER("std parallel");
    std::for_each(std::execution::par, numbers_std_para.begin(), numbers_std_para.end(), [](int& i) { i = i * 2; });
  }
}

struct ReduceInteger {
  std::vector<int>* numbers = nullptr;
  size_t sum = 0;

  ReduceInteger() = default;
  ReduceInteger(const ReduceInteger& rhs, split) : numbers(rhs.numbers) {}
  ReduceInteger(const ReduceInteger& rhs) = default;
  void operator()(size_t i) { sum += numbers->at(i); }
  void merge(const ReduceInteger& rhs) { sum += rhs.sum; }
};

void test_parallel_reduce() {
  constexpr size_t size = 100'000'000;
  std::vector<int> numbers(size, 1);

  size_t sum_parallel_for;
  size_t sum_std_sum;

  {
    TIMER("parallel_reduce");
    ReduceInteger reduce;
    reduce.numbers = &numbers;
    parallel_reduce(0, size, reduce, 10'000'000);
    sum_parallel_for = reduce.sum;
  }

  {
    TIMER("std accumulate");
    sum_std_sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  }

  if (sum_parallel_for != sum_std_sum) {
    std::cout << "Failed\n";
  }
}

int main(int argc, char** argv) {
  test_parallel_reduce();
  return 0;
}