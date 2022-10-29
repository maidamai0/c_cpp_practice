#include <iostream>

class Base {
 public:
  Base() { virtual_func(); };

  virtual void virtual_func() { std::cout << __FUNCTION__ << std::endl; }
};

class Derived : public Base {
 public:
  Derived() { virtual_func(); };

  void virtual_func() override { std::cout << __FUNCTION__ << std::endl; }
};

auto main(int argc, char** argv) -> int {
  Derived d;
  (void)d;  // make compiler silent
}