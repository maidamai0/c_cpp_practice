#include "2.class_template_argument_deduction.hpp"
#include "dispatch.hpp"

int main(int argc, char** argv) {
  auto s = Stack(1);
  auto s2 = Stack("hello");
  Stack s3 = {"hello"};

  to_unsigned(1);
  to_unsigned(1u);
  return 0;
}