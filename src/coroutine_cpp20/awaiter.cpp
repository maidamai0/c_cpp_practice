#include <chrono>
#include <coroutine>
#include <thread>

#include "trace.hpp"

struct suspend_always {
  bool await_ready() const noexcept {
    trace;
    return false;
  }

  void await_suspend(std::coroutine_handle<> h) const noexcept {
    trace;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  void await_resume() const noexcept { trace; }
};

struct suspend_never {
  bool await_ready() const noexcept {
    trace;
    return true;
  }

  void await_suspend(std::coroutine_handle<> h) const noexcept { trace; }
  void await_resume() const noexcept { trace; }
};

struct return_object {
  struct promise_type {
    promise_type() { trace; };
    return_object get_return_object() {
      trace;
      return {std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    suspend_always initial_suspend() {
      trace;
      return {};
    }

    suspend_always final_suspend() noexcept {
      trace;
      return {};
    }

    void return_value(int v) { trace; }

    // void return_void(int v) { trace; }

    void unhandled_exception() noexcept { trace; }
  };

  return_object(std::coroutine_handle<promise_type> h) : h_(h) { trace; }
  operator std::coroutine_handle<>() {
    trace;
    return h_;
  }

  std::coroutine_handle<> h_;
};

return_object foo() {
  trace;
  co_await suspend_always{};
}

int main(int argc, char** argv) {
  std::coroutine_handle<> h = foo();
  h.resume();
  h.resume();
  //   h.resume();
  return 0;
}