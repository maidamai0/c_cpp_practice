#include "static.h"

auto StaticLib::GetSum() const -> double {
  return d_ + static_cast<double>(f_) + static_cast<double>(i_);
}