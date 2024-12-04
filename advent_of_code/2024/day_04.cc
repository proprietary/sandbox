#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace {
auto read_lines() -> std::vector<std::string> {
  std::vector<std::string> res;
  std::string line;
  while (std::getline(std::cin, line)) {
    res.push_back(line);
  }
  return res;
}

auto part_1(const std::vector<std::string>& rows) -> int {
  constexpr std::string_view xmas{"XMAS"};
  constexpr std::string_view samx{"SAMX"};
  constexpr int l = xmas.length();
  int res = 0;
  const int n = rows.size();
  const int m = rows[0].size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (rows[i][j] == 'X') {
        std::string west;
        for (int j2 = j; j2 > std::max(-1, j - l); --j2) {
          west.push_back(rows[i][j2]);
        }
        if (west == xmas || west == samx) res++;
        const auto east = rows[i].substr(j, l);
        if (east == xmas || east == samx) res++;
        std::string north;
        for (int i2 = i; i2 > std::max(-1, i - l); --i2) {
          north.push_back(rows[i2][j]);
        }
        if (north == xmas || north == samx) res++;
        std::string south;
        for (int i2 = i; i2 < std::min(n, i + l); ++i2) {
          south.push_back(rows[i2][j]);
        }
        assert(south.length() <= l);
        if (south == xmas || south == samx) res++;
        std::string north_east;
        for (int i2 = i, j2 = j;
             i2 > std::max(-1, i - l) && j2 < std::min(m, j + l); --i2, ++j2) {
          north_east.push_back(rows[i2][j2]);
        }
        assert(north_east.length() <= l);
        if (north_east == xmas || north_east == samx) res++;
        std::string south_east;
        for (int i2 = i, j2 = j;
             i2 < std::min(n, i + l) && j2 < std::min(m, j + l); ++i2, ++j2) {
          south_east.push_back(rows[i2][j2]);
        }
        assert(south_east.length() <= l);
        if (south_east == xmas || south_east == samx) res++;
        std::string south_west;
        for (int i2 = i, j2 = j;
             i2 < std::min(n, i + l) && j2 > std::max(-1, j - l); ++i2, --j2) {
          south_west.push_back(rows[i2][j2]);
        }
        assert(south_west.length() <= l);
        if (south_west == xmas || south_west == samx) res++;
        std::string north_west;
        for (int i2 = i, j2 = j;
             i2 > std::max(-1, i - l) && j2 > std::max(-1, j - l); --i2, --j2) {
          north_west.push_back(rows[i2][j2]);
        }
        assert(north_west.length() <= l);
        if (north_west == xmas || north_west == samx) res++;
      }
    }
  }
  return res;
}

auto part_2(const std::vector<std::string>& rows) -> int {
  assert(rows.size() > 0);
  assert(rows[0].size() > 0);

  int res = 0;
  constexpr std::string_view mas{"MAS"};
  constexpr std::string_view sam{"SAM"};
  const int n = rows.size();
  const int m = rows[0].size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (rows[i][j] == 'A') {
        std::string diag1;
        if (i - 1 > -1 && j - 1 > -1) diag1.push_back(rows[i - 1][j - 1]);
        diag1.push_back(rows[i][j]);
        if (i + 1 < n && j + 1 < m) diag1.push_back(rows[i + 1][j + 1]);
        std::string diag2;
        if (i + 1 < n && j - 1 > -1) diag2.push_back(rows[i + 1][j - 1]);
        diag2.push_back(rows[i][j]);
        if (i - 1 > -1 && j + 1 < m) diag2.push_back(rows[i - 1][j + 1]);
        if ((diag1 == mas || diag1 == sam) && (diag2 == mas || diag2 == sam)) {
          res++;
        }
      }
    }
  }
  return res;
}

TEST(Part1, Sample) {
  const std::vector<std::string> input = {
      {"MMMSXXMASM"}, {"MSAMXMSMSA"}, {"AMXSXMAAMM"}, {"MSAMASMSMX"},
      {"XMASAMXAMM"}, {"XXAMMXXAMA"}, {"SMSMSASXSS"}, {"SAXAMASAAA"},
      {"MAMMMXMMMM"}, {"MXMXAXMASX"},
  };
  EXPECT_EQ(part_1(input), 18);
}

TEST(Part2, Sample) {
  const std::vector<std::string> input = {
      {"MMMSXXMASM"}, {"MSAMXMSMSA"}, {"AMXSXMAAMM"}, {"MSAMASMSMX"},
      {"XMASAMXAMM"}, {"XXAMMXXAMA"}, {"SMSMSASXSS"}, {"SAXAMASAAA"},
      {"MAMMMXMMMM"}, {"MXMXAXMASX"},
  };
  EXPECT_EQ(part_2(input), 9);
}
}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  assert(RUN_ALL_TESTS() == 0);
  std::vector<std::string> rows = read_lines();
  std::cout << part_1(rows) << '\n' << part_2(rows) << '\n';
  return 0;
}
