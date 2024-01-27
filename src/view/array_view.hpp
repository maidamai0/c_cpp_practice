
#pragma once

#include <cassert>
#include <cstddef>

template <typename T, int D>
class array_buffer {
 public:
  using ref_ptr = T*;
  static constexpr auto dimension = D;

  class iterator {
   public:
    using reference = array_buffer<T, D>;
    using ptr = array_buffer<T, D>*;
  };

  array_buffer(ref_ptr data, size_t size) : data_(data), size_(size) { assert(size / D && "size can not divide D"); }

  ref_ptr operator[](int i) {
    const auto idx = i * D;
    assert(idx <= (size_ - D) && "index out of bound");
    return data_ + idx;
  }

  size_t size() const { return size_ / D; }

 private:
  ref_ptr data_ = nullptr;
  size_t size_ = 0;
};

template <typename T>
class array_buffer<T, 1> {
 public:
  using ref_ptr = T*;
  static constexpr auto dimension = 1;

  array_buffer(ref_ptr data, size_t size) : data_(data), size_(size) {}

  T operator[](int i) {
    assert(i < size_ && "index out of bound");
    return data_[i];
  }

  size_t size() const { return size_; }

 private:
  ref_ptr data_ = nullptr;
  size_t size_ = 0;
};