#pragma once

template <typename Func>
class ScopeGuard {
 public:
  ScopeGuard(Func&& func) : func_{func} {};
  ~ScopeGuard() { func_(); }

 private:
  Func func_;
};

template <typename Func>
auto make_scope_guard(Func&& func) {
  return ScopeGuard(std::move(func));
}