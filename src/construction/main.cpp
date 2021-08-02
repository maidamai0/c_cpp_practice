#include <initializer_list>
#include <iostream>
#include <iterator>
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

class Init {
 public:
  Init(int a, int b) : a_(a), b_(b) {
    std::cout << "Init(int a, int b)" << '\n';
  }

  Init() { std::cout << "Init()" << '\n'; }

  Init(std::initializer_list<double> il) {
    std::cout << "Init(std::initializer_list<double> il)" << '\n';
    a_ = std::data(il)[0];
    b_ = std::data(il)[1];
  }

  int a_;
  int b_;
};

void test_init_list() {
  Init a(1, 2);
  std::cout << a.a_ << " " << a.b_ << std::endl;

  Init b = {3.0, 4.0};
  std::cout << b.a_ << " " << b.b_ << std::endl;

  Init c = {3, 4};
  std::cout << b.a_ << " " << b.b_ << std::endl;

  Init d = {};
  Init e = {{}};
}

auto main(int argc, char** argv) -> int {
  Foo foo{{"base1", 2}, 1, 2, 3}; // How `foo` is constructed, any constructor get called?
  foo.print();

  Foo foo1{{"base2", 2}, 1, 2, 3, "string", 3};
  foo1.print();

  test_init_list();
}