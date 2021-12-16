#pragma once

#include <memory>

class Foo {
 public:
  Foo();
  ~Foo();
  void DoSomething();

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};