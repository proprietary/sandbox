#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
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

  int part_1 = 0;

  for (size_t i = 0; i < left_column.size(); ++i) {
    part_1 += std::abs(left_column[i] - right_column[i]);
  }

  // part 1
  std::cout << part_1 << '\n';

  std::unordered_map<int, int> right_column_frequency;
  right_column_frequency.reserve(right_column.size());
  for (const int x : right_column) {
    right_column_frequency[x]++;
  }

  int64_t similarity_score = 0;
  for (const int x : left_column) {
    similarity_score += x * right_column_frequency[x];
  }

  // part 2
  std::cout << similarity_score << '\n';

  return 0;
}
