#include <iostream>
#include <regex>
#include <string>
#include <string_view>

int main(int argc, char* argv[], char* envp[]) {
  int part_1 = 0, part_2 = 0;
  const std::regex re{R"(mul\((\d+),(\d+)\))"};
  constexpr std::string_view enable{"do()"};
  constexpr std::string_view disable{"don't()"};

  bool enabled = true;
  std::string input;
  std::string line;
  while (std::getline(std::cin, line)) {
    input += line;
  }
  // part 1
  {
    for (auto it = std::sregex_iterator(input.begin(), input.end(), re);
         it != std::sregex_iterator(); ++it) {
      const int a = std::stoi(it->str(1));
      const int b = std::stoi(it->str(2));
      part_1 += a * b;
    }
  }
  // part 2
  for (auto start = input.begin(); start != input.end();) {
    if (!enabled) {
      start = std::search(start, input.end(), enable.begin(), enable.end());
      if (start != input.end()) {
        start += enable.length();
      }
    }
    auto end = std::search(start, input.end(), disable.begin(), disable.end());
    if (end != input.end()) {
      enabled = false;
    }
    for (auto it = std::sregex_iterator(start, end, re);
         it != std::sregex_iterator(); ++it) {
      const int a = std::stoi(it->str(1));
      const int b = std::stoi(it->str(2));
      part_2 += a * b;
    }
    start = end;
  }
  std::cout << part_1 << '\n' << part_2 << '\n';
  return 0;
}
