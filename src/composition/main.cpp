#include <iostream>
#include <string>
#include <type_traits>

template <typename F>
auto Compose(F&& f) {
  return [=](auto x) { return f(x); };
}

template <typename F, typename... Fs>
auto Compose(F&& f, Fs... fs) {
  return [=](auto x) { return f(Compose(fs...)(x)); };
}

template <typename F>
auto Select(F&& f) {
  return [=](auto&&... xs) {
    static_assert(std::is_invocable_v<F, decltype(xs)...>, "not invokable");
    return f(xs...);
  };
}

template <typename F, typename... Fs>
auto Select(F&& f, Fs... fs) {
  return [=](auto&&... xs) {
    if constexpr (std::is_invocable_v<F, decltype(xs)...>) {
      return f(xs...);
    } else {
      return Compose(fs...)(xs...);
    }
  };
}

auto main(int argc, char** argv) -> int {
  {
    const auto fun = Compose([](int x) { return std::to_string(x); });
    std::cout << fun(3) << std::endl;
  }

  {
    const auto fun = Compose([](int x) { return std::to_string(x); }, [](int x) { return x * x; });
    std::cout << fun(3) << std::endl;
  }

  {
    const auto fun = Select([](int x, int y, std::string&& str) { return std::to_string(x + y) + str; });
    std::cout << fun(3, 5, "fds") << std::endl;
    // std::cout << fun("str") << std::endl; // trigger an error
  }

  {
    const auto fun = Select([](std::string x) { return x; }, [](int x) { return x * x; });
    std::cout << fun(3) << std::endl;
    std::cout << fun("str") << std::endl;
  }
}