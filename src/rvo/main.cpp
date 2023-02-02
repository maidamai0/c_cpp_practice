#include <string>
#include <vector>

#include "fmt/core.h"
#include "fmt/format.h"

struct Foo {
  Foo() { fmt::print("{}\n", __FUNCTION__); }
  ~Foo() { fmt::print("{}\n", __FUNCTION__); }
  Foo(Foo&& f) { fmt::print("{}\n", __FUNCTION__); }
  Foo(Foo& f) { fmt::print("{}\n", __FUNCTION__); }

  std::string s_;
  std::string s1_;
  std::string s2_;
  int i_;
};

auto get_foo() {
  Foo foo;
  foo.i_ = 1;
  foo.s_ = "foo";
  foo.s1_ = "bar";
  foo.s2_ = "baz";
  return foo;
}

auto get_foo1() {
  return Foo();
}

auto get_vector_foo() {
  std::vector<Foo> foos;
  foos.reserve(4);
  foos.emplace_back();
  foos.emplace_back();

  return foos;
}

auto main(int argc, char** argv) -> int {
  { auto foo = get_foo(); }
  { auto ves = get_vector_foo(); }
  { auto foo1 = get_foo1(); }
}