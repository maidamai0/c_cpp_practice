#include "2.class_template_argument_deduction.hpp"

int main(int argc, char** argv) {
  auto s = Stack(1);
  auto s2 = Stack("hello");
  Stack s3 = {"hello"};
  return 0;
}