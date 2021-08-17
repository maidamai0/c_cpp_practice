#include <string>
#include <vector>

#include "fmt/format.h"

struct Foo {
  Foo() { fmt::print("Foo::Foo()\n"); }
  ~Foo() { fmt::print("Foo::~Foo()\n"); }
  // Foo(Foo&& f) { fmt::print("Foo::Foo(Foo&&)\n"); }

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

auto main(int argc, char** argv) -> int {
  auto foo = get_foo();
  fmt::print("foo.i_ = {}\n", foo.i_);
}