#include <coroutine>
#include <iostream>

struct fun_trace {
  fun_trace(std::string_view name) : name_{name} {
    std::cout << std::string(ident_, ' ') << ">>>> " << name_ << '\n';
    ident_ += 4;
  }

  ~fun_trace() {
    ident_ -= 4;
    std::cout << std::string(ident_, ' ') << "<<<< " << name_ << '\n';
  }

  std::string_view name_;
  thread_local static size_t ident_;
};

thread_local size_t fun_trace::ident_ = 0;

#define trace fun_trace _trace(__FUNCTION__)

struct ReturnObject {
  struct promise_type {
    promise_type() = default;
    ReturnObject get_return_object() {
      trace;
      return {};
    }
    // std::suspend_always initial_suspend() {
    //   trace;
    //   return {};
    // }
    std::suspend_never initial_suspend() {
      trace;
      return {};
    }
    std::suspend_never final_suspend() noexcept {
      trace;
      return {};
    }
    int return_value(int v) {
      trace;
      return v;
    }
    void unhandled_exception() { trace; }
  };
};

void do_nothing() {
  trace;
}

ReturnObject empty_coroutine() {
  trace;
  // co_await std::suspend_always{};
  co_await std::suspend_never{};
}

int main(int argc, char const *argv[]) {
  trace;
  auto v = empty_coroutine();
  return 0;
}
