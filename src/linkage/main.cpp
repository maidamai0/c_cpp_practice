#include <string>

#include "liba.h"
#include "linkage/liba.h"

int main(int argc, char** argv) {
  foo(0);
  foo(false);
  foo(1.0f);
  foo("abc");
  foo(std::string("string"));

  return 0;
}