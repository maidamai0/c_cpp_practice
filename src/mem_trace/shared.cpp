#include "shared.h"
#include <iostream>

void SharedLib::Print() {
  std::cout << a_ << s_ << d_ << std::endl;
}