#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[], char *envp[]) {
  std::vector<int> left_column;
  std::vector<int> right_column;
  {
    std::string line;
    while (std::getline(std::cin, line)) {
      std::stringstream ss{line};
      std::string column;
      ss >> column;
      left_column.push_back(std::stoi(column));
      ss >> column;
      right_column.push_back(std::stoi(column));
    }
  }

  assert(left_column.size() == right_column.size());

  std::ranges::sort(left_column);
  std::ranges::sort(right_column);

  int ans = 0;

  for (size_t i = 0; i < left_column.size(); ++i) {
    ans += std::abs(left_column[i] - right_column[i]);
  }

  std::cout << ans;

  return 0;
}
