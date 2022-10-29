#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

template <int a>
struct A {
  static constexpr int value = a;
};

template <typename... Args>
void print(Args... args) {
  (std::cout << ... << args) << std::endl;
}

void print() {
}

template <typename T, typename... Args>
void print(T a, Args... args) {
  std::cout << a << " ";
  print(args...);
}

template <typename Func, typename... Args>
void Call(Func f, Args... args) {
  f(args...);
}

class Foo {
 public:
  Foo() = default;

  std::ostream& operator<<(std::ostream& os) const {
    os << "Foo{" << value_ << "}\n";
    return os;
  }

 private:
  friend std::ostream& operator<<(std::ostream& os, const Foo& foo) { return foo.operator<<(os); }

 private:
  int value_ = 0;
};

template <typename T, size_t size>
class array {};

template <typename T, typename... U>
array(T, U...) -> array<std::enable_if_t<(std::is_same_v<T, U> && ...), T>, (1 + sizeof...(U))>;

int main(int argc, char** argv) {
  Foo foo;
  foo.operator<<(std::cout);      // calls the Foo::operator<<(std::ostream&)
  std::cout << foo << std::endl;  // calls the friend operator<<

  std::cout << A<1>::value << std::endl;

  print(1, 2, 3, 4, 5);

  Call([](int a, std::string_view s, double d) { std::cout << a << " " << s << " " << d << std::endl; }, 1, "hello",
       3.14);

  // array a{1, 2, 3, 4};
  array<int, 4> ddd2;

  return 0;
}