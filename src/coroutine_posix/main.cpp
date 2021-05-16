#include <signal.h>
#include <ucontext.h>
#include <unistd.h>

#include <iostream>

#include "common/scope_trace.h"
#include "coroutine.h"
#include "fmt/format.h"

void loop() {
  FUNC_TRACE;
  ucontext_t ctx = {0};
  getcontext(&ctx);  // Loop start
  fmt::print("Hello World\n");
  std::flush(std::cout);
  sleep(1);
  setcontext(&ctx);  // Loop end
}

void assign(uint32_t* var, uint32_t val) {
  FUNC_TRACE;
  *var = val;
}

void switch_ctx() {
  FUNC_TRACE;
  uint32_t var = 0;
  ucontext_t ctx = {0}, back = {0};
  getcontext(&ctx);
  ctx.uc_stack.ss_sp = calloc(1, MINSIGSTKSZ);
  ctx.uc_stack.ss_size = MINSIGSTKSZ;
  ctx.uc_stack.ss_flags = 0;
  ctx.uc_link = &back;  // Will get back to main as `swapcontext` call will
                        // populate `back` with current context
  // ctx.uc_link = 0;  // Will exit directly after `swapcontext` call
  makecontext(&ctx, (void (*)())assign, 2, &var, 100);
  swapcontext(&back, &ctx);  // Calling `assign` by switching context
  printf("var = %d\n", var);
}

void coroutine() {
  const auto func = [](Coroutine& cor) {
    TRACE("coroutine func");
    {
      TRACE("co.Yield");
      cor.Yield(3);
    }
    return 1;
  };
  Coroutine crt(func);
  for (size_t i = 0; i < 5; i++) {
    fmt::print("Resume return:{}\n", crt.Resume());
    std::flush(std::cout);
  }
}

int main() {
  coroutine();
  return 0;
}