#include <vector>

#include "fmt/format.h"

class Foo {
 public:
  [[nodiscard]] auto GetList() -> std::vector<int>& { return list_; }

  void Print() const {
    fmt::print("list content is:\n");
    for (const auto& value : list_) {
      fmt::print("{} ", value);
    }
    fmt::print("\n");
  }

 private:
  std::vector<int> list_{1, 2, 3};
};

auto main(int argc, char** argv) -> int {
  Foo foo;

  // original
  fmt::print("Original ");
  foo.Print();

  // raw auto
  Foo foo_raw;
  auto list = foo_raw.GetList();
  list.insert(list.end(), {4, 5, 6, 7});
  fmt::print("Raw auto ");
  foo_raw.Print();

  // raw type
  Foo foo_raw_type;
  std::vector<int> list_raw_type = foo_raw_type.GetList();
  list_raw_type.insert(list_raw_type.end(), {4, 5, 6, 7});
  fmt::print("Raw type ");
  foo_raw_type.Print();

  // auto with referecne
  Foo foo_ref;
  auto& list_ref = foo_ref.GetList();
  list_ref.insert(list_ref.end(), {4, 5, 6, 7});
  fmt::print("Reference auto ");
  foo_ref.Print();

  // raw type
  Foo foo_reference_type;
  std::vector<int>& list_reference_type = foo_reference_type.GetList();
  list_reference_type.insert(list_reference_type.end(), {4, 5, 6, 7});
  fmt::print("Reference type ");
  foo_reference_type.Print();

  // Temp
  Foo foo_temp;
  foo_temp.GetList().insert(foo_temp.GetList().end(), {4, 5, 6, 7});
  fmt::print("Temp ");
  foo_temp.Print();
}