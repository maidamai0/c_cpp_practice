#include <array>
#include <cstddef>
#include <cstdint>
#include <ios>
#include <iostream>
#include <typeinfo>

class Class1 {
public:
  Class1() = default;

private:
  double double_data_{};
};

class Class2 {
public:
  Class2() = default;

private:
  char char_data_{};
};

class Class3 {
  int data_{};
};

class Class4 {
  char data_[2];
};

class Class5 {
  char data_[3];
};

class Class6 {
  char data_[4];
};

class Class7 {
  char data_[5];
};

class Class8 {
  char data_[7];
};

struct Class9 {
  char data_[9];
};

template <typename T>
auto print_alignment() {
  std::cout << "Alignment of " << typeid(T).name() << " is " << alignof(T) << "; ";

  auto* object = new T();
  std::boolalpha(std::cout);
  std::cout << "address can be divided by its alignment: "
            << !static_cast<bool>(reinterpret_cast<std::uintptr_t>(object) % alignof(T)) << std::endl;
  delete object;
}

template <typename T>
auto check_address() {
}

auto main(int argc, char** argv) -> int {
  print_alignment<std::max_align_t>();
  print_alignment<Class1>();
  print_alignment<Class2>();
  print_alignment<Class3>();
  print_alignment<Class4>();
  print_alignment<Class5>();
  print_alignment<Class6>();
  print_alignment<Class7>();
  print_alignment<Class8>();
  print_alignment<Class9>();
}