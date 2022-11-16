#include <concepts>
#include <iostream>
#include <variant>

#include "fmt/core.h"
#include "fmt/format.h"

template <typename T>
concept Printable = requires(T t, int i) {
                      { t.PrintName() } -> std::convertible_to<void>;
                      { t.Add(i) } -> std::convertible_to<int>;
                    };

class Derived {
 public:
  void PrintName() const { fmt::print("{}\n", __FUNCTION__); }
  int Add(int i) const {
    int ret = __LINE__ + 1;
    fmt::print("{} add i is {}\n", __FUNCTION__, ret);
    return ret;
  }
};

class ExtraDerived {
 public:
  void PrintName() const { fmt::print("{}\n", __FUNCTION__); };
  int Add(int i) const {
    int ret = __LINE__ + 1;
    fmt::print("{} add i is {}\n", __FUNCTION__, ret);
    return ret;
  }
};

struct CallPrintName {
  void operator()(const Derived& d) { d.PrintName(); }
  void operator()(const ExtraDerived& d) { d.PrintName(); }
};

void call_with_struct() {
  fmt::print("{}\n", __FUNCTION__);
  std::variant<Derived, ExtraDerived> d;
  std::visit(CallPrintName{}, d);

  d = ExtraDerived();
  std::visit(CallPrintName(), d);
}

void call_with_lambda() {
  fmt::print("{}\n", __FUNCTION__);
  int i = 9;
  std::variant<Derived, ExtraDerived> d;
  std::visit([](const Printable auto& d) { d.PrintName(); }, d);
  std::visit([i](const Printable auto& d) { d.Add(i); }, d);

  d = ExtraDerived();
  std::visit([](const Printable auto& d) { d.PrintName(); }, d);
  std::visit([i](const Printable auto& d) { d.Add(i); }, d);
}

int main(int argc, char** argv) {
  call_with_struct();
  fmt::print("\n");
  call_with_lambda();
  return 0;
}