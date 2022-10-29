#include <nanobench.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

constexpr auto cache_size_w = 50;
constexpr auto cache_size_h = 50;
using MatrixType = std::array<std::array<int, cache_size_w>, cache_size_h>;
nlohmann::json memory;

auto cache_h_w() {
  MatrixType matrix{};
  auto counter = 0;

  for (auto i = 0; i < cache_size_h; ++i) {
    for (auto j = 0; j < cache_size_w; ++j) {
      memory["data"].push_back(
          {{"x", counter++}, {"address", reinterpret_cast<intptr_t>(&matrix[i][j])}, {"legend", "h_w"}});
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto cache_h_w_reverse() {
  MatrixType matrix{};
  auto counter = 0;
  for (auto i = 0; i < cache_size_h; ++i) {
    for (auto j = 0; j < cache_size_w; ++j) {
      memory["data"].push_back(
          {{"x", counter++}, {"address", reinterpret_cast<intptr_t>(&matrix[j][i])}, {"legend", "h_w_reverse"}});
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto cache_w_h() {
  MatrixType matrix{};
  auto counter = 0;
  for (auto i = 0; i < cache_size_w; ++i) {
    for (auto j = 0; j < cache_size_h; ++j) {
      memory["data"].push_back(
          {{"x", counter++}, {"address", reinterpret_cast<intptr_t>(&matrix[i][j])}, {"legend", "w_h"}});
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto cache_w_h_reverse() {
  MatrixType matrix{};
  auto counter = 0;
  for (auto i = 0; i < cache_size_w; ++i) {
    for (auto j = 0; j < cache_size_h; ++j) {
      memory["data"].push_back(
          {{"x", counter++}, {"address", reinterpret_cast<intptr_t>(&matrix[j][i])}, {"legend", "w_h_reverse"}});
    }
  }

  ankerl::nanobench::doNotOptimizeAway(counter);
}

auto main(int argc, char** argv) -> int {
  memory["title"] = "Memory usage";

  ankerl::nanobench::Bench().run("cache_h_w", cache_h_w);
  ankerl::nanobench::Bench().run("cache_h_w_reverse", cache_h_w_reverse);
  ankerl::nanobench::Bench().run("cache_w_h", cache_w_h);
  ankerl::nanobench::Bench().run("cache_w_h_reverse", cache_w_h_reverse);

  ankerl::nanobench::Bench().run("cache_h_w", cache_h_w);
  ankerl::nanobench::Bench().run("cache_h_w_reverse", cache_h_w_reverse);
  ankerl::nanobench::Bench().run("cache_w_h", cache_w_h);
  ankerl::nanobench::Bench().run("cache_w_h_reverse", cache_w_h_reverse);

  std::ofstream of("memory_usage.json");
  of << std::setw(2) << memory;
}
