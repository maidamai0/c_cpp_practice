#include <coroutine>
#include <iostream>

#include "trace.hpp"

class promise_impl {
 public:
  promise_impl() { trace; }
  ~promise_impl() { trace; }
  void get_return_object_imp() { trace; }
  void initial_suspend_imp() { trace; }
  void find_suspend_imp() { trace; }
  void return_value_imp() { trace; }
  void unhandled_exception_imp() { trace; }

 private:
};

struct ReturnObject {
  struct promise_type {
    promise_type() = default;
    ReturnObject get_return_object() {
      trace;
      impl_.get_return_object_imp();
      return {std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    std::suspend_always initial_suspend() {
      trace;
      impl_.initial_suspend_imp();
      return {};
    }

    std::suspend_always final_suspend() noexcept {
      trace;
      impl_.find_suspend_imp();
      return {};
    }

    int return_value(int v) {
      trace;
      impl_.return_value_imp();
      return v;
    }

    void unhandled_exception() {
      trace;
      impl_.unhandled_exception_imp();
    }

   private:
    promise_impl impl_;
  };

  ReturnObject(std::coroutine_handle<promise_type> h) : handle_(h) {}
  operator std::coroutine_handle<>() const { return handle_; }

  std::coroutine_handle<> handle_;
};

void do_nothing() {
  trace;
}

ReturnObject empty_coroutine() {
  trace;
  co_await std::suspend_always{};
  // co_await std::suspend_never{};
}

int main(int argc, char const *argv[]) {
  trace;
  std::coroutine_handle<> cor = empty_coroutine();
  cor.resume();
  cor.resume();
  return 0;
}
