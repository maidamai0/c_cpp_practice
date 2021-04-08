#include <fmt/format.h>

#include <iostream>
#include <ostream>
#include <string>

// make a concept
template <typename T>
concept Addable = requires(T x) {
  x + x;
};

template <typename T>
concept Comparable = requires(T x) {
  x < x;
};

template <typename T>
concept Serialiable = requires(T x) {
  std::cout << x;
};

template <typename T>
concept HasFoo = requires(T x) {
  x.foo();
};

template <typename T>
concept HasBar = requires(T x) {
  x.bar();
};

// use a concept
template <typename T>
requires Addable<T>&& Comparable<T>&& Serialiable<T> auto UseAddConcept(T a,
                                                                        T b) {
  return a + b;
}

struct Foo {
  Foo operator+(const Foo& b) {
    Foo c;
    return c;
  }

  void foo() {}

  bool operator<(const Foo a) { return true; }
};

std::ostream& operator<<(std::ostream& os, const Foo a) {
  return os;
}

struct Bar {
  void bar() {}
};

struct FooBar {
  void foo() {}
  void bar() {}
};

template <typename T>
requires HasFoo<T> void call_foo(T x) {
  x.foo();
}

template <typename T>
requires HasBar<T> void call_bar(T x) {
  x.bar();
}

template <typename T>
requires HasBar<T>&& HasFoo<T> void call_foo_bar(T x) {
  x.foo();
  x.bar();
}

int main(int argc, char** argv) {
  // i is addable
  auto i_a = 0;
  auto i_b = 1;
  const auto i_sum = UseAddConcept(i_a, i_b);
  fmt::print("int sum is {}\n", i_sum);

  // const char* is *NOT* addable, clang has much more readble error messages
  // auto s_a = "a";
  // auto s_b = "b";
  // const auto s_sum = UseAddConcept(s_a, s_b);
  // fmt::print("std::string sum is {}\n", s_sum);

  // std::string is addable
  auto str_a = std::string("a");
  auto str_b = std::string("b");
  const auto str_sum = UseAddConcept(str_a, str_b);
  fmt::print("std::string sum is {}\n", str_sum);

  Foo f_a;
  Foo f_b;
  const auto f_sum = UseAddConcept(f_a, f_b);

  Foo foo;
  Bar bar;
  FooBar foo_bar;
  call_foo(foo);
  call_bar(bar);
  call_foo_bar(foo_bar);

  return 0;
}