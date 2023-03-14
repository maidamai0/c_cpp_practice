#include <algorithm>
#include <execution>
#include <vector>

#include "common/scope_timer.h"
#include "parallel_algorithm/parallel_for.h"

int main(int argc, char** argv) {
  constexpr size_t size = 1000'000'000;
  //   std::vector<int> numbers_serial(size);
  std::vector<int> numbers_para(size);
  std::vector<int> numbers_std_para(size);

  {
    TIMER("parallel_for");
    parallel_for(
        0, size, [&numbers_para](int i) { numbers_para[i] = i * 2; }, 500'000'000);
  }

  //   {
  //     TIMER("serial");
  //     for (int i = 0; i < size; ++i) {
  //       numbers_serial[i] = i * 2;
  //     }
  //   }

  {
    TIMER("std parallel");
    std::for_each(std::execution::par, numbers_std_para.begin(), numbers_std_para.end(), [](int i) { return i * 2; });
  }

  return 0;
}