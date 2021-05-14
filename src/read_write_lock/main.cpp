#include "fmt/format.h"
#include <vector>

class Foo {
public:
  [[nodiscard]] auto GetList() -> std::vector<int>& {
    return list_;
  }

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
}