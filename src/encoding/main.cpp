#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>

std::string widechar_to_utf8(const std::wstring& wstr) {
  std::string utf8_str;
  int utf8_str_size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, 0, 0, 0, 0);
  if (utf8_str_size > 0) {
    std::vector<char> buffer(utf8_str_size);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &buffer[0], utf8_str_size, 0, 0);
    utf8_str.assign(buffer.begin(), buffer.end() - 1);
  }
  return utf8_str;
}

std::wstring utf8_to_widechar(const std::string& str) {
  std::wstring wstr;
  int wstr_size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, 0, 0);
  if (wstr_size > 0) {
    std::vector<wchar_t> buffer(wstr_size);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &buffer[0], wstr_size);
    wstr.assign(buffer.begin(), buffer.end() - 1);
  }
  return wstr;
}

void test_filename() {
  const auto fn = utf8_to_widechar("中文.txt");  // OK
  std::ofstream ofs(fn);
  ofs << "中文";
  ofs.close();

  const auto fn1 = std::wstring(L"中文1.txt");  // error
  std::ofstream ofs1(fn1);
  ofs1 << "中文1";
  ofs1.close();

  const auto fn2 = utf8_to_widechar("中文2.txt");  // OK
  const auto temp_fn = std::string("temp.txt");
  std::ofstream ofs2(temp_fn);
  ofs2 << "中文2";
  ofs2.close();
  std::filesystem::rename(temp_fn, fn2);
}
#endif

auto main(int argc, char** argv) -> int {
  std::string chinese = "你好世界";
  std::string english = "helloworld!";

  const auto chinese_size = chinese.size();
  const auto english_size = english.size();

  std::cout << chinese << " size is " << chinese_size << std::endl;
  std::cout << english << " size is " << english_size << std::endl;

#ifdef WIN32
  test_filename();
#endif
}