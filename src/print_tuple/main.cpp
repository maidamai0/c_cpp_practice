#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename T>
void print_element(const T& e) {
  std::cout << e << ',';
}

template <typename tuple, std::size_t... Is>
void print_tuple_1(const tuple& tp) {
  (print_element(std::get<Is>(tp)), ...);
}

template <typename tuple, std::size_t... Is>
void print_tuple_2(const tuple& tp, std::index_sequence<Is...>) {
  (print_element(std::get<Is>(tp)), ...);
}

template <typename tuple>
void print_tuple_3(const tuple& tp) {
  print_tuple_2(tp, std::make_index_sequence<std::tuple_size_v<tuple>>{});
}

auto main() -> int {
  std::tuple tp{10, 20, "hello"};

  {
    std::cout << "print_tuple_1: ";
    print_tuple_1<decltype(tp), 0, 1, 2>(tp);
    std::cout << '\n';
  }

  {
    std::cout << "print_tuple_2: ";
    print_tuple_2(tp, std::index_sequence<0, 1, 2>{});
    std::cout << '\n';
  }

  {
    std::cout << "print_tuple_3: ";
    print_tuple_3(tp);
    std::cout << '\n';
  }
  return 0;
}