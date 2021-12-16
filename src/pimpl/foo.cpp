#include "foo.h"

#include <iostream>
#include <memory>

class Foo::Impl {
 public:
  Impl() { std::cout << __FUNCTION__ << std::endl; }
  ~Impl() { std::cout << __FUNCTION__ << std::endl; }
  void DoSomething() { std::cout << __FUNCTION__ << std::endl; }
};

Foo::Foo() : impl_(std::make_unique<Impl>()) {
  std::cout << __FUNCTION__ << std::endl;
}

Foo::~Foo() = default;

void Foo::DoSomething() {
  std::cout << __FUNCTION__ << std::endl;
  return impl_->DoSomething();
}