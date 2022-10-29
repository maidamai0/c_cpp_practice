#pragma once

#include <atomic>

class ReadWriteLock final {
 public:
  ReadWriteLock();
  void Read();
  void Write();

  ReadWriteLock(const ReadWriteLock&) = delete;
  auto operator=(const ReadWriteLock&) -> ReadWriteLock& = delete;
  ReadWriteLock(ReadWriteLock&&) = delete;
  auto operator=(ReadWriteLock&&) -> ReadWriteLock& = delete;

 private:
  std::atomic_uint64_t num_reader_;
};