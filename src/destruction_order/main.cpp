#include <iostream>
#include <thread>

#include "fmt/format.h"

class ChildA final {
public:
  ChildA() {
    fmt::print("{}\n", __FUNCTION__);
  }

  static auto Instance() -> auto& {
    static ChildA instance;
    return instance;
  }

  ~ChildA() {
    fmt::print("{}\n", __FUNCTION__);
  }
};

class ChildB final {
public:
  ChildB() {
    fmt::print("{}\n", __FUNCTION__);
  }

  static auto Instance() -> auto& {
    static ChildB instance;
    return instance;
  }

  ~ChildB() {
    fmt::print("{}\n", __FUNCTION__);
  }
};

class Parent final {
public:
  Parent() {
    fmt::print("{}\n", __FUNCTION__);
  }

  static auto Instance() -> auto& {
    static Parent instance;
    return instance;
  }

  ~Parent() {
    fmt::print("{}\n", __FUNCTION__);
    delete child_a_;
    delete child_b_;
  }

  ChildA* child_a_ = nullptr;
  ChildB* child_b_ = nullptr;
};

ChildB b;

auto main(int argc, char* argv[]) -> int {
  auto& parent = Parent::Instance();

  auto& a = ChildA::Instance();
  // parent.child_a_ = &a; // will crash if we comment out this line.

  // b = new ChildB();
  // parent.child_b_ = &b;
}