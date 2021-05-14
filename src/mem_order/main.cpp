#include <atomic>
#include <cassert>
#include <iostream>
#include <string>
#include <thread>

constexpr auto loop = 1000;

// TEST_CASE("sequencial consistency") {
//   for (int i = 0; i < loop; ++i) {
//     std::atomic_bool task1_ready = false;
//     std::atomic_bool task2_ready = false;
//     std::string result;

//     std::thread t1([&] {
//       result = "1";
//       task1_ready.store(true);

//       while (!task2_ready) {
//         ;
//       }
//       result += "3";
//     });

//     std::thread t2([&] {
//       while (!task1_ready.load()) {
//         ;
//       }
//       result += "2";
//       task2_ready.store(true);
//     });

//     t1.join();
//     t2.join();

//     CHECK(result == "123");
//   }
// }

// TEST_CASE("test2") {
//   for (int i = 0; i < loop; ++i) {
//     std::atomic_bool task1_ready = false;
//     std::atomic_bool task2_ready = false;
//     std::string result;

//     std::thread t1([&] {
//       result = "1";
//       task1_ready.store(true, std::memory_order_relaxed);

//       while (!task2_ready.load(std::memory_order_relaxed)) {
//         ;
//       }
//       result += "3";
//     });

//     std::thread t2([&] {
//       while (!task1_ready.load(std::memory_order_relaxed)) {
//         ;
//       }
//       result += "2";
//       task2_ready.store(true, std::memory_order_relaxed);
//     });

//     t1.join();
//     t2.join();

//     CHECK(result == "123");
//   }
// }

auto main() -> int {
  for (int i = 0; i < loop; ++i) {
    std::atomic_int x = 0;
    std::atomic_int y = 0;

    constexpr auto order = std::memory_order_relaxed;

    std::thread t1([&] {
      y.store(20, order);
      x.store(10, order);
    });

    std::thread t2([&] {
      if (x.load(order) == 10) {
        assert(y.load(order) == 20);
        y.store(10, order);
      }
    });

    std::thread t3([&] {
      if (y.load(order) == 10) {
        assert(x.load(order) == 10);
      }
    });

    t1.join();
    t2.join();
    t3.join();
  }
}

// TEST_CASE("relaxed") {
//   for (int i = 0; i < loop; ++i) {
//     std::atomic_bool ready = false;
//     std::string result;

//     std::thread t1([&] {
//       while (!ready.load(std::memory_order_relaxed)) {
//         ;
//       }
//       result += "task2";
//     });

//     std::thread t2([&] {
//       result = "task1 ";
//       ready.store(true, std::memory_order_relaxed);
//     });

//     t1.join();
//     t2.join();

//     CHECK(result == "task1 task2");
//   }
// }