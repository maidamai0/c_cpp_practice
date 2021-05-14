#include <memory>

class AllPublic {
public:
  AllPublic() = default;
  AllPublic(int a){};
  ~AllPublic() = default;
};

class PrivateConstructor {
private:
  PrivateConstructor() = default;
  PrivateConstructor(int){};

public:
  static std::shared_ptr<PrivateConstructor> create() {
    return std::shared_ptr<PrivateConstructor>(new PrivateConstructor());
  }

  ~PrivateConstructor() = default;
};

class PrivateDestructor {
public:
  PrivateDestructor() = default;

private:
  ~PrivateDestructor() = default;
};

class AllPrivate {
private:
  AllPrivate() = default;
  ~AllPrivate() = default;
};

auto make_shared() {
  auto all_public = std::make_shared<AllPublic>();
  //   auto private_ctor = std::make_shared<PrivateConstructor>();
  //   auto private_dctor = std::make_shared<PrivateDestructor>();
  //   auto all_private = std::make_shared<AllPrivate>();
}

auto Construct_with_new() {
  std::shared_ptr<AllPublic> all_public(new AllPublic(1));

  auto raw_ptr = new AllPublic(1);
  std::shared_ptr<AllPublic> sptr(raw_ptr);

  std::shared_ptr<PrivateConstructor> private_ctor;
  std::shared_ptr<PrivateDestructor> private_dctor;
  std::shared_ptr<AllPrivate> all_private;
}

auto raw_new() {
  std::shared_ptr<AllPublic> all_public;
  std::shared_ptr<PrivateConstructor> private_ctor;
  std::shared_ptr<PrivateDestructor> private_dctor;
  std::shared_ptr<AllPrivate> all_private;
}

int main() {
  make_shared();
  raw_new();
}