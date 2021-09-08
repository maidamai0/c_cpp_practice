#include <iostream>
#include <string>

class foo {
 public:
  foo(std::string s) : s_(s) { std::cout << "foo()" << std::endl; }
  ~foo() { std::cout << "~foo()" << std::endl; }

  foo(const foo& rhs) {
    std::cout << "foo(const foo&)" << std::endl;
    s_ = rhs.s_;
  }
  foo& operator=(const foo& rhs) {
    std::cout << "foo& operator=(const foo&)" << std::endl;
    s_ = rhs.s_;
    return *this;
  }

  foo(foo&& rhs) {
    std::cout << "foo(foo&&)" << std::endl;
    s_ = std::move(rhs.s_);
  }
  foo& operator=(foo&&) {
    std::cout << "foo& operator=(foo&&)" << std::endl;
    s_ = std::move(s_);
    return *this;
  }

  void print() const { std::cout << s_ << std::endl; }

 private:
  std::string s_;
};

void const_ref(const foo& f) {
  std::cout << "const_ref(const foo&)" << std::endl;
  f.print();
}

void right_ref(foo&& f) {
  std::cout << "right_ref(foo&&)" << std::endl;
  f.print();
}

int main(int argc, char** argv) {
  {
    foo f("123456789abcdefghijklmnopqrstuvwxyz");
    const_ref(f);
    f.print();
  }
  std::cout << "----------------" << std::endl;
  {
    foo f("123456789abcdefghijklmnopqrstuvwxyz");
    const_ref(std::move(f));
    f.print();
  }
  std::cout << "----------------" << std::endl;
  {
    foo f("123456789abcdefghijklmnopqrstuvwxyz");
    right_ref(std::move(f));
    f.print();
  }
  return 0;
}