#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <array>
#include <cassert>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

namespace {

auto parse(std::istream& is) -> std::vector<std::vector<int>> {
  std::vector<std::vector<int>> map;
  std::string line;
  while (std::getline(is, line)) {
    std::vector<int> row;
    for (const auto& c : line) {
      row.push_back(c - '0');
    }
    map.emplace_back(std::move(row));
  }
  return map;
}

constexpr std::array<std::array<int, 2>, 4> DIRECTIONS{
    std::array<int, 2>{-1, 0}, std::array<int, 2>{0, 1},
    std::array<int, 2>{1, 0}, std::array<int, 2>{0, -1}};

auto score(const std::vector<std::vector<int>>& map, const int start_row,
           const int start_col) -> int {
  int res = 0;
  std::vector<std::vector<bool>> visited(
      map.size(), std::vector<bool>(map[0].size(), false));
  std::stack<std::pair<int, int>> s;
  s.emplace(start_row, start_col);
  while (!s.empty()) {
    const auto [row, col] = s.top();
    s.pop();
    const int cur = map[row][col];
    for (const auto& direction : DIRECTIONS) {
      const int row2 = row + direction[0];
      const int col2 = col + direction[1];
      if (row2 >= 0 && row2 < map.size() && col2 >= 0 && col2 < map[0].size() &&
          !visited[row2][col2]) {
        const int next = map[row2][col2];
        if (next == cur + 1) {
          if (next == 9) {
            visited[row2][col2] = true;
            res++;
          } else {
            visited[row2][col2] = true;
            s.emplace(row2, col2);
          }
        }
      }
    }
  }
  return res;
}

auto solve_part_1(const std::vector<std::vector<int>>& map) -> int {
  int res = 0;
  for (int i = 0; i < map.size(); ++i) {
    assert(map[i].size() == map[0].size());
    for (int j = 0; j < map[i].size(); ++j) {
      if (map[i][j] == 0) {
        const int a = score(map, i, j);
        res += a;
      }
    }
  }
  return res;
}

auto rating(const std::vector<std::vector<int>>& map, const int start_row,
            const int start_col) -> int {
  int res = 0;
  std::stack<std::pair<int, int>> s;
  s.emplace(start_row, start_col);
  while (!s.empty()) {
    const auto [row, col] = s.top();
    s.pop();
    const int cur = map[row][col];
    for (const auto& direction : DIRECTIONS) {
      const int row2 = row + direction[0];
      const int col2 = col + direction[1];
      if (row2 >= 0 && row2 < map.size() && col2 >= 0 && col2 < map[0].size()) {
        const int next = map[row2][col2];
        if (next == cur + 1) {
          if (next == 9) {
            res++;
          } else {
            s.emplace(row2, col2);
          }
        }
      }
    }
  }
  return res;
}

auto solve_part_2(const std::vector<std::vector<int>>& map) -> int {
  int res = 0;
  for (int i = 0; i < map.size(); ++i) {
    assert(map[i].size() == map[0].size());
    for (int j = 0; j < map[i].size(); ++j) {
      if (map[i][j] == 0) {
        const int a = rating(map, i, j);
        res += a;
      }
    }
  }
  return res;
}

std::string EXAMPLE = R"(89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732)";

TEST(Part1, Example) {
  std::istringstream input{EXAMPLE};
  const auto parsed = parse(input);
  const int actual = solve_part_1(parsed);
  ASSERT_EQ(actual, 36);
}

TEST(Part2, Example) {
  std::istringstream input{EXAMPLE};
  const auto parsed = parse(input);
  const int actual = solve_part_2(parsed);
  ASSERT_EQ(actual, 81);
}
}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  assert(RUN_ALL_TESTS() == 0);
  const auto parsed = parse(std::cin);
  const int part_1 = solve_part_1(parsed);
  fmt::println("{}", part_1);
  const int part_2 = solve_part_2(parsed);
  fmt::println("{}", part_2);
  return 0;
}
