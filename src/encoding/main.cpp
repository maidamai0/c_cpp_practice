#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

auto main(int argc, char** argv) -> int {
  std::string chinese = "你好世界";
  std::string english = "helloworld!";

  const auto chinese_size = chinese.size();
  const auto english_size = english.size();

  std::cout << chinese << " size is " << chinese_size << std::endl;
  std::cout << english << " size is " << english_size << std::endl;

  std::filesystem::path path("中文.txt");
  std::ofstream ofs(path);
  ofs << chinese;
  ofs << "中文";
}