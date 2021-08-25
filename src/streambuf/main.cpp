#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <ostream>
#include <streambuf>

class myoutbuf : public std::streambuf {
 protected:
  int_type overflow(int_type c = traits_type::eof()) override {
    if (c != traits_type::eof()) {
      c = std::toupper(static_cast<char>(c), getloc());
      if (putchar(c) == EOF) {
        return traits_type::eof();
      }
    }

    return c;
  }
};

int main(int argc, char** argv) {
  myoutbuf ob;
  std::ostream os(&ob);
  os << "31 hexadeicmal: " << std::hex << 31 << std::endl;
  return EXIT_SUCCESS;
}