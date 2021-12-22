#include <iostream>
#include <ostream>

class Foo {
 public:
  Foo() = default;

  std::ostream& operator<<(std::ostream& os) const {
    os << "Foo{" << value_ << "}\n";
    return os;
  }

 private:
  friend std::ostream& operator<<(std::ostream& os, const Foo& foo) {
    return foo.operator<<(os);
  }

 private:
  int value_ = 0;
};

int main(int argc, char** argv) {
  Foo foo;
  foo.operator<<(std::cout);      // calls the Foo::operator<<(std::ostream&)
  std::cout << foo << std::endl;  // calls the friend operator<<
  return 0;
}