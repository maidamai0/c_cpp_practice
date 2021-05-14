#include <cstdio>
#include <iostream>
#include <ostream>
#include <thread>
#include <vector>

// #include "fmt/format.h"

void foo() {
  [[maybe_unused]] static bool unused = [] {
    printf("printed once");
    return true;
  }();
}

class SingleTon;

static SingleTon* instance = nullptr;

class SingleTon {
public:
  static auto GetInstance() -> auto* {
    [[maybe_unused]] static auto init = []() {
      printf("initialization code\n");
      instance = new SingleTon;
      return true;
    }();

    return instance;
  }

private:
  SingleTon() {
    printf("%s\n", __FUNCTION__);
  }
};

constexpr auto thread_num = 200;

auto main() -> int {
  std::vector<std::thread> ts;
  ts.reserve(thread_num);
  for (int i = 0; i < thread_num; ++i) {
    ts.emplace_back(foo);
    SingleTon::GetInstance();
  }

  for (auto&& t : ts) {
    t.join();
  }
}