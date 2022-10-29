#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"

/**
 * @brief base class for test iterators
 *
 */
class range_base {
 protected:
  std::vector<int> data_ = std::vector<int>(200, 0);
};

class custom_iterator : public range_base {
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

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.ptr_ == rhs.ptr_; }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs.ptr_ != rhs.ptr_; }

   private:
    pointer ptr_ = nullptr;
  };

  Iterator begin() { return Iterator(&data_[0]); };
  Iterator end() { return Iterator(&data_[200]); }
};

class use_std_iterator : public range_base {
 public:
  struct iterator : public std::iterator<std::forward_iterator_tag, int> {
    explicit iterator(int* ptr) : ptr_(ptr) {}
    iterator& operator++() {
      ++ptr_;
      return *this;
    }

    iterator operator++(int) {
      const auto retval = *this;
      ++ptr_;
      return retval;
    }

    friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.ptr_ == rhs.ptr_; }

    friend bool operator!=(const iterator& lhs, const iterator& rhs) { return lhs.ptr_ != rhs.ptr_; }

    reference operator*() const { return *ptr_; }

   private:
    pointer ptr_;
  };

  iterator begin() { return iterator(&data_[0]); };
  iterator end() { return iterator(&data_[200]); }
};

template <typename RangeType>
void test() {
  fmt::print("Test {}\n", typeid(RangeType).name());
  RangeType ints;
  int cnt = 0;
  std::cout << "original:\n";
  for (const auto i : ints) {
    assert(i == 0);
    ++cnt;
  }
  assert(cnt == 200);

  std::fill(ints.begin(), ints.end(), 100);
  std::cout << "all 100\n";
  cnt = 0;
  for (const auto i : ints) {
    assert(i == 100);
    ++cnt;
  }
  assert(cnt == 200);
}

TEST_CASE("iterator") {
  test<custom_iterator>();
  test<use_std_iterator>();
}