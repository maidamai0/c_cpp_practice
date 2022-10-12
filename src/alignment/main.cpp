#include <array>
#include <cstddef>
#include <cstdint>
#include <ios>
#include <iostream>
#include <thread>
#include <typeinfo>

#include "nanobench.h"

class Class1 {
public:
  Class1() = default;

 private:
  double double_data_{};
};
class Class1Alignas {
 public:
  Class1Alignas() = default;

 private:
  alignas(16) double double_data_{};
};

class Class2 {
public:
  Class2() = default;

private:
  char char_data_{};
};

class Class3 {
  int data_{};
};

class Class4 {
  char data_[2];
};

class Class5 {
  char data_[3];
};

class Class6 {
  char data_[4];
};

class Class7 {
  char data_[5];
};

class Class8 {
  char data_[7];
};

struct Class9 {
  char data_[9];
};

template <typename T>
auto print_alignment() {
  std::cout << "Alignment of " << typeid(T).name() << " is " << alignof(T) << "; ";

  auto* object = new T();
  std::boolalpha(std::cout);
  std::cout << "address can be divided by its alignment: "
            << !static_cast<bool>(reinterpret_cast<std::uintptr_t>(object) % alignof(T)) << std::endl;
  delete object;
}

void increment(int* p) {
  for (int i = 0; i < 100'000'000; ++i) {
    *p += 1;
  }
}

void f() {
  int i0 = 0;
  int i1 = 0;

  std::thread t0(&increment, &i0);
  std::thread t1(&increment, &i0);

  t0.join();
  t1.join();
}

void f_align() {
  alignas(256) int i0 = 0;
  alignas(256) int i1 = 0;

  std::thread t0(&increment, &i0);
  std::thread t1(&increment, &i0);

  t0.join();
  t1.join();
}

alignas(8) int a = 0;

auto main(int argc, char** argv) -> int {
  print_alignment<std::max_align_t>();
  print_alignment<Class1>();
  print_alignment<Class1Alignas>();
  print_alignment<Class2>();
  print_alignment<Class3>();
  print_alignment<Class4>();
  print_alignment<Class5>();
  print_alignment<Class6>();
  print_alignment<Class7>();
  print_alignment<Class8>();
  print_alignment<Class9>();

  ankerl::nanobench::Bench().run("no alignas", f);
  ankerl::nanobench::Bench().run("alignas(64)", f);
}