#include "read_write_lock.h"

#include <cstdint>
#include <limits>
#include <thread>

namespace {
constexpr auto max_retry_num = 5;
constexpr auto reader_num_for_writer = std::numeric_limits<uint64_t>::max();  // 0xffff ffff
}  // namespace

void ReadWriteLock::Read() {
  auto retry = 0;
  while (true) {
    auto prev_readers = num_reader_.load();

    if (prev_readers != reader_num_for_writer) {
      if (num_reader_.compare_exchange_weak(prev_readers, prev_readers + 1)) {
        return;
      }
    }

    if (++retry > max_retry_num) {
      // sleep and retry again
      retry = 0;
      std::this_thread::yield();
    }
  }
}

void ReadWriteLock::Write() {
  int retry = 0;
  while (true) {
    auto prev_readers = num_reader_.load();
    if (prev_readers == 0) {
      if (num_reader_.compare_exchange_weak(prev_readers, reader_num_for_writer)) {
        return;
      }
    }

    if (++retry > max_retry_num) {
      retry = 0;
      std::this_thread::yield();
    }
  }
}