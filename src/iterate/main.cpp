#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

#include "fmt/core.h"

class integers {
 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    Iterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }
    Iterator& operator++() {
      ++ptr_;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

   private:
    pointer ptr_ = nullptr;
  };

  Iterator begin() { return Iterator(&data_[0]); };
  Iterator end() { return Iterator(&data_[200]); }

 private:
  std::vector<int> data_ = std::vector<int>(200, 0);
};

int main(int argc, char** argv) {
  integers ints;
  std::cout << "original:\n";
  for (const auto i : ints) {
    std::cout << i << std::endl;
  }

  std::fill(ints.begin(), ints.end(), 100);
  std::cout << "all 100\n";
  for (const auto i : ints) {
    std::cout << i << std::endl;
  }
  return 0;
}