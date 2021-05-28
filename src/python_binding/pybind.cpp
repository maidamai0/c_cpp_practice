#include "module.h"
#include "pybind11/detail/common.h"
#include "pybind11/pybind11.h"

PYBIND11_MODULE(cppmodule, m) {
  m.doc() = "pybin11 example plugin";
  m.doc() = ("hello", &hello, "return hello message");
}