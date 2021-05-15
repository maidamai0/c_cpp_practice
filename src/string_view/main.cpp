#include "fmt/format.h"
#include "magic_enum.hpp"

#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <variant>

enum class EnumTest { Prefix_First, PRefix_Second_element };

auto get_name(EnumTest e) {
  auto s = magic_enum::enum_name(e);
  auto str = std::string(s.substr(7, s.size()));
  for (auto& c : str) {
    if (c == '_') {
      c = ' ';
    }
  }

  return str;
}

auto main(int argc, char** argv) -> int {
  constexpr auto date = std::string_view(__DATE__);
  constexpr auto day = date.substr(4, 2);
  constexpr auto month = date.substr(0, 3);
  constexpr auto year = date.substr(date.size() - 4, 4);

  const auto get_month_digit = [](std::string_view month) constexpr {
    if (month == "Jan") {
      return 1;
    }
    if (month == "Feb") {
      return 2;
    }
    if (month == "Mar") {
      return 3;
    }
    if (month == "Apr") {
      return 4;
    }
    if (month == "May") {
      return 5;
    }
    if (month == "Jun") {
      return 6;
    }
    if (month == "Jul") {
      return 7;
    }
    if (month == "Aug") {
      return 8;
    }
    if (month == "Sep") {
      return 9;
    }
    if (month == "Oct") {
      return 10;
    }
    if (month == "Nov") {
      return 11;
    }
    if (month == "Dec") {
      return 12;
    }
    return 0;
  };

  fmt::print("date is [{}], year is [{}], month is [{}], day is [{}]\n", date, year, month, day);
  std::fflush(stdout);

  auto date_digit = fmt::format("{}/{}/{}", day, get_month_digit(month), year);
  fmt::print("Date digit is [{}]\n", date_digit);
  std::fflush(stdout);

  const auto day_digit = std::atoi(day.data());
  constexpr auto month_digit = get_month_digit(month);
  const auto year_digit = std::atoi(year.data() + 2);

  fmt::print("Date digit is [{}]\n", fmt::format("{}/{}/{}", day_digit, month_digit, year_digit));
  std::fflush(stdout);

  fmt::print("ts is [{}]\n", fmt::format("{:02}/{:02}/{}",day_digit, month_digit, year_digit));
  std::fflush(stdout);

  // constexpr auto year_digit = (year[2] - '0') * 10 + (year[3] - '0');
  // constexpr auto month_digit = get_month_digit(year);
  // constexpr auto day_digit =

  fmt::print("{}\n", get_name(EnumTest::Prefix_First));
  fmt::print("{}\n", get_name(EnumTest::PRefix_Second_element));

  return 0;
}