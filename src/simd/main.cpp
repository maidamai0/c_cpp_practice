#include <nanobench.h>
#include <xmmintrin.h>

#include <cassert>
#include <chrono>
#include <iostream>
#include <string_view>

class timer {
  using clock_t = std::chrono::steady_clock;

 public:
  explicit timer(const std::string_view& name) : name_(name), start_(clock_t::now()) {}
  ~timer() {
    auto end = std::chrono::steady_clock::now();
    std::cout << name_ << " cost time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_).count()
              << std::endl;
  }

 private:
  std::string_view name_;
  clock_t::time_point start_;
};

#define TIMER timer _timer(__FUNCTION__);
// #define TIMER

void naive() {
  float a[4] = {1.0f, 2.0, 3.0f, 4.0};
  float b[4] = {1.0f, 2.0, 3.0f, 4.0};
  float c[4] = {};

  {
    TIMER;
    for (int i = 0; i < 4; ++i) {
      c[i] = a[i] + b[i];
    }
  }

  for (int i = 0; i < 3; ++i) {
    assert(c[i] == 2.0 * (i + 1));
  }
}

void simd() {
  float a[4] = {1.0f, 2.0, 3.0f, 4.0};
  float b[4] = {1.0f, 2.0, 3.0f, 4.0};
  float c[4] = {};

  {
    TIMER;
    __m128 c1 = _mm_add_ps(reinterpret_cast<__m128&>(a), reinterpret_cast<__m128&>(b));
    _mm_storeu_ps(c, c1);
  }

  for (int i = 0; i < 3; ++i) {
    assert(c[i] == 2.0 * (i + 1));
  }
}

int main(int argc, char** argv) {
  //   ankerl::nanobench::Bench().run("naive: ", naive);
  //   ankerl::nanobench::Bench().run("simd : ", simd);

  for (int i = 0; i < 10; ++i) {
    simd();
    naive();
  }

  simd();
  naive();
}