#include <iostream>
#include <mutex>
#include <string>

#include "shared.h"
#include "static.h"

std::mutex mtx;

auto operator new(size_t size) -> void* {
  {
    // std::cout << "Allocating " << size << " bytes\n";
    printf("Allocating %zu bytes\n", size);
  }
  return malloc(size);
}

auto operator delete(void* p, size_t size) noexcept -> void {
  {
    std::lock_guard<std::mutex> lock(mtx);
    // std::cout << "Freeing " << size << " bytes\n";
    printf("Freeing %zu bytes\n", size);
  }
  free(p);
}

auto operator delete(void* p) noexcept -> void {
  {
    std::lock_guard<std::mutex> lock(mtx);
    // std::cout << "Freeing " << size << " bytes\n";
    printf("Freeing unknow bytes\n");
  }
  free(p);
}

class Object {
 public:
  Object() = default;
  ~Object() = default;

 private:
  int a_;
  int b_;
};

auto main(int argc, char** argv) -> int {
  {
    auto* object = new Object();
    delete object;
    printf("\n");
  }

  {
    auto* object = new StaticLib;
    delete object;
    printf("\n");
  }

  {
    auto* object = new SharedLib;
    delete object;
    printf("\n");
  }

  {
    auto* str = new std::string;
    delete str;
    printf("\n");
  }

  {
    auto* str = new std::string(
        "sgfhdsfads fjdsfjlkdsafjkladsjfidsajfliadsjfoiadsjfiadsjflkadsjflkadsnfkdsalfhadsfjh;fasdfsdfgadgagfdfasgs");
    delete str;
    printf("\n");
  }

  return 0;
}