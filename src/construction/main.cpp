#include <iostream>
#include <string>
#include <vector>

class Base {
public:
  std::string str_mem;
  int int_val = 0;
};

class Bar {
public:
  Bar() = default;
  Bar(int val) : int_val(val) {
  }

  auto GetVal() {
    return int_val;
  }

private:
  int int_val = 0;
};

class Foo : public Base {
public:
  int mem_1;
  int mem_2;
  int mem_3;

  std::string str_mem;
  Bar class_mem;

  auto print() {
    printf("[%d,%d,%d,%s,%d]\n", mem_1, mem_2, mem_3, str_mem.c_str(), class_mem.GetVal());
  }
};

auto main(int argc, char** argv) -> int {
  Foo foo{{"base1", 2}, 1, 2, 3}; // How `foo` is constructed, any constructor get called?
  foo.print();

  Foo foo1{{"base2", 2}, 1, 2, 3, "string", 3};
  foo1.print();
}