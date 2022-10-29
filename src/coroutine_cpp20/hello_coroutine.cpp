#include <coroutine>
#include <iostream>

struct HelloWorldCoro {
  struct promise_type {  // compiler looks for `promise_type`
    HelloWorldCoro get_return_object() { return this; }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
  HelloWorldCoro(promise_type* p) : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
  ~HelloWorldCoro() { m_handle.destroy(); }
  std::coroutine_handle<promise_type> m_handle;
};

HelloWorldCoro print_hello_world() {
  std::cout << "Hello ";
  co_await std::suspend_always{};
  std::cout << "World!" << std::endl;
}

int main() {
  HelloWorldCoro mycoro = print_hello_world();
  mycoro.m_handle.resume();
  mycoro.m_handle();  // Equal to mycoro.m_handle.resume();
  return EXIT_SUCCESS;
}