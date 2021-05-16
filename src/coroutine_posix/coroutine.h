#pragma once

#include <signal.h>
#include <ucontext.h>

#include <functional>

#include "common/scope_trace.h"

class Coroutine;
void entry_point(Coroutine* cor);

class Coroutine {
  using func_t = std::function<int(Coroutine& cor)>;
  friend void entry_point(Coroutine*);

 public:
  Coroutine(func_t func) : function_(func) {
    FUNC_TRACE;
    resume_context_.uc_stack.ss_sp = calloc(1, MINSIGSTKSZ);
    resume_context_.uc_stack.ss_size = MINSIGSTKSZ;
    resume_context_.uc_link = nullptr;

    getcontext(&resume_context_);
    makecontext(&resume_context_, (void (*)()) & entry_point, 1, this);
  }

  ~Coroutine() {
    FUNC_TRACE;
    free(resume_context_.uc_stack.ss_sp);
  }

  int Resume() {
    FUNC_TRACE;
    if (finished_) {
      return -1;
    }

    swapcontext(&suspend_context_, &resume_context_);
    return yield_value_;
  }

  void Yield(int value) {
    FUNC_TRACE;
    yield_value_ = value;
    swapcontext(&resume_context_, &suspend_context_);
  }

 private:
  func_t function_;
  ucontext_t suspend_context_ = {0};
  ucontext_t resume_context_ = {0};
  int yield_value_ = 0;
  bool finished_ = false;
};

void entry_point(Coroutine* cor) {
  FUNC_TRACE;
  int ret = cor->function_(*cor);
  cor->finished_ = true;
  cor->Yield(ret);
}