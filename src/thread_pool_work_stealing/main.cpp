#include "task_system.hpp"

int main(int argc, char** argv) {
  task_system tasks;
  for (size_t i = 0; i < 100; ++i) {
    tasks.async([i]() {
      std::this_thread::sleep_for(std::chrono::milliseconds((i % 4) + 1) * 500);
      std::cout << "task #" << i << " finished" << std::endl;
    });
  }

  return 0;
}