#pragma once

class StaticLib {
 public:
  StaticLib() = default;
  ~StaticLib() = default;

  [[nodiscard]] auto GetSum() const -> double;

 private:
  double d_ = 0.0;
  float f_ = 0.0F;
  int i_ = 0;
};