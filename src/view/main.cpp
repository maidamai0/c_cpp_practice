#include <cstdio>
#include <format>
#include <numeric>
#include <vector>

#include "array_view.hpp"

int main(int argc, char** argv) {
  std::vector<int> vec(100);
  std::iota(vec.begin(), vec.end(), 0);

  {
    array_buffer<int, 1> buffer(vec.data(), vec.size());
    assert(buffer.size() == 100);
    for (size_t i = 0; i < buffer.size(); ++i) {
      assert(buffer[i] == i);
    }
  }

  {
    array_buffer<int, 2> buffer(vec.data(), vec.size());
    assert(buffer.size() == 50);
    for (size_t i = 0; i < buffer.size(); ++i) {
      auto* data = buffer[i];
      for (int j = 0; j < buffer.dimension; ++j) {
        assert(data[j] == i * buffer.dimension + j);
      }
    }
  }

  {
    array_buffer<int, 4> buffer(vec.data(), vec.size());
    assert(buffer.size() == 25);
    for (size_t i = 0; i < buffer.size(); ++i) {
      auto* data = buffer[i];
      for (int j = 0; j < buffer.dimension; ++j) {
        assert(data[j] == i * buffer.dimension + j);
      }
    }
  }

  return 0;
}