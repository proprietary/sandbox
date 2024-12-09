#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
struct Location {
  int row;
  int col;

  bool operator==(const Location& other) const {
    return row == other.row && col == other.col;
  }
};

struct LocationHash {
  std::size_t operator()(const Location& location) const {
    return std::hash<int>{}(location.row) ^
           (std::hash<int>{}(location.col) << 1);
  }
};

struct Parsed {
  std::unordered_map<char, std::vector<Location>> m;
  int rows;
  int cols;
};

auto gcd(int a, int b) -> int {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

auto parse(std::istream& is) -> Parsed {
  std::unordered_map<char, std::vector<Location>> m;
  std::string line;
  int cols = 0;
  int row = 0;
  while (std::getline(is, line)) {
    if (cols == 0) {
      cols = line.length();
    }
    for (int col = 0; col < line.length(); ++col) {
      if (line[col] != '.') {
        m[line[col]].emplace_back(row, col);
      }
    }
    ++row;
  }
  return Parsed{.m = m, .rows = row, .cols = cols};
}

auto solve(const Parsed& p) -> std::pair<int, int> {
  std::unordered_set<Location, LocationHash> part_1, part_2;
  auto within_grid = [&p](const Location& x) -> bool {
    return x.row >= 0 && x.row < p.rows && x.col >= 0 && x.col < p.cols;
  };
  for (const auto& [freq, locations] : p.m) {
    for (int i = 0; i < locations.size(); ++i) {
      for (int j = i + 1; j < locations.size(); ++j) {
        int dr = locations[j].row - locations[i].row;
        int dc = locations[j].col - locations[i].col;
        Location antinode1{.row = locations[i].row - dr,
                           .col = locations[i].col - dc};
        if (within_grid(antinode1)) {
          part_1.insert(antinode1);
        }
        Location antinode2{.row = locations[j].row + dr,
                           .col = locations[j].col + dc};
        if (within_grid(antinode2)) {
          part_1.insert(antinode2);
        }

        const int divisor = gcd(std::abs(dr), std::abs(dc));
        dr = dr / divisor;
        dc = dc / divisor;
        Location cur = locations[i];
        while (within_grid(cur)) {
          part_2.insert(cur);
          cur.row += dr;
          cur.col += dc;
        }
        cur = locations[i];
        while (within_grid(cur)) {
          part_2.insert(cur);
          cur.row -= dr;
          cur.col -= dc;
        }
      }
    }
  }
  return {part_1.size(), part_2.size()};
}

auto solve(std::istream& input) -> std::pair<int, int> {
  const auto p = parse(input);
  return solve(p);
}

std::string EXAMPLE{R"(............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............)"};

TEST(Part1, Example) {
  std::istringstream input{EXAMPLE};
  const auto [part_1, _] = solve(input);
  ASSERT_EQ(part_1, 14);
}

TEST(Part2, Example) {
  std::istringstream input{EXAMPLE};
  const auto [_, part_2] = solve(input);
  ASSERT_EQ(part_2, 34);
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  assert(RUN_ALL_TESTS() == 0);
  const auto [part_1, part_2] = solve(std::cin);
  fmt::println("{}\n{}", part_1, part_2);
  return 0;
}
