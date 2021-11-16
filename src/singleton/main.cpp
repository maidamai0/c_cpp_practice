#include <iostream>

class Singleton1 {
 public:
  static Singleton1* GetInstance() {
    static Singleton1 instance;
    return &instance;
  }

  Singleton1() { std::cout << "Singleton1()" << std::endl; }
  ~Singleton1() { std::cout << "Singleton1 destroyed" << std::endl; }
};

class Singleton2 {
 public:
  static Singleton2* GetInstance() {
    static Singleton2 instance;
    return &instance;
  }

  Singleton2() { std::cout << "Singleton2()" << std::endl; }
  ~Singleton2() { std::cout << "Singleton2 destroyed" << std::endl; }
};

class Singleton3 {
 public:
  static Singleton3* GetInstance() {
    static Singleton3 instance;
    return &instance;
  }

  Singleton3() { std::cout << "Singleton3()" << std::endl; }
  ~Singleton3() { std::cout << "Singleton3 destroyed" << std::endl; }
};

class Singleton4 {
 public:
  static Singleton4* GetInstance() {
    static Singleton4 instance;
    return &instance;
  }
  Singleton4() { std::cout << "Singleton4()" << std::endl; }
  ~Singleton4() { std::cout << "Singleton4 destroyed" << std::endl; }
};

int main(int argc, char** argv) {
  auto* s1 = Singleton1::GetInstance();
  auto s2 = Singleton2::GetInstance();
  auto s3 = Singleton3::GetInstance();
  auto s4 = Singleton4::GetInstance();
  return 0;
}