#include <gtest/gtest.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "tools/cpp/runfiles/runfiles.h"

namespace {
using namespace std;
class Solution {
  size_t R, C;
  std::vector<std::string> grid;
  std::vector<std::vector<bool>> visited;
  int area = 0, fences = 0, perimeter = 0;

  int neighbors(int r, int c) {
    if (r < 0 || r >= R || c < 0 || c >= C) {
      return ' ';
    }
    return grid[r][c];
  }

  void dfs(const int r, const int c, const int target) {
    if (visited[r][c]) {
      return;
    } else {
      visited[r][c] = true;
    }
    area++;
    if (neighbors(r - 1, c) != target && neighbors(r, c - 1) != target) {
      fences++;
    }
    if (neighbors(r - 1, c) != target && neighbors(r, c + 1) != target) {
      fences++;
    }
    if (neighbors(r + 1, c) != target && neighbors(r, c + 1) != target) {
      fences++;
    }
    if (neighbors(r + 1, c) != target && neighbors(r, c - 1) != target) {
      fences++;
    }
    if (neighbors(r, c + 1) == target && neighbors(r + 1, c) == target &&
        neighbors(r + 1, c + 1) != target) {
      fences++;
    }
    if (neighbors(r - 1, c) == target && neighbors(r, c + 1) == target &&
        neighbors(r - 1, c + 1) != target) {
      fences++;
    }
    if (neighbors(r, c - 1) == target && neighbors(r + 1, c) == target &&
        neighbors(r + 1, c - 1) != target) {
      fences++;
    }
    if (neighbors(r, c - 1) == target && neighbors(r - 1, c) == target &&
        neighbors(r - 1, c - 1) != target) {
      fences++;
    }
    if (neighbors(r - 1, c) != target) {
      perimeter++;
    } else {
      dfs(r - 1, c, target);
    }
    if (neighbors(r + 1, c) != target) {
      perimeter++;
    } else {
      dfs(r + 1, c, target);
    }
    if (neighbors(r, c - 1) != target) {
      perimeter++;
    } else {
      dfs(r, c - 1, target);
    }
    if (neighbors(r, c + 1) != target) {
      perimeter++;
    } else {
      dfs(r, c + 1, target);
    }
  }

  public:
  Solution(std::istream &is) {
    std::string line;
    while (std::getline(is, line)) {
      grid.push_back(line);
    }
    R = grid.size();
    C = grid[0].size();
    visited = std::vector<std::vector<bool>>(R, std::vector<bool>(C, false));
  }

  auto solve() -> std::pair<uint64_t, uint64_t> {
    uint64_t part_1 = 0, part_2 = 0;
    for (int r = 0; r < R; r++) {
      for (int c = 0; c < C; c++) {
        if (!visited[r][c]) {
          area = fences = perimeter = 0;
          dfs(r, c, grid[r][c]);
          part_1 += area * perimeter;
          part_2 += area * fences;
        }
      }
    }
    return {part_1, part_2};
  }
};

::bazel::tools::cpp::runfiles::Runfiles *runfiles;

std::string EXAMPLE = R"(RRRRIICCFF
RRRRIICCCF
VVRRRCCFFF
VVRCCCJFFF
VVVVCJJCFE
VVIVCCJJEE
VVIIICJJEE
MIIIIIJJEE
MIIISIJEEE
MMMISSJEEE)";

TEST(Part1, Example) {
  std::istringstream iss{EXAMPLE};
  const auto [part_1, _] = Solution{iss}.solve();
  ASSERT_EQ(part_1, 1930);
}

TEST(Part2, Example) {
  std::istringstream iss{EXAMPLE};
  const auto [_, part_2] = Solution{iss}.solve();
  ASSERT_EQ(part_2, 1206);
}

TEST(Part1, Input) {
  std::ifstream input{
      runfiles->Rlocation("_main/advent_of_code/2024/day_12_input.txt")};
  const auto [part_1, _] = Solution{input}.solve();
  ASSERT_EQ(part_1, 1461806);
}

TEST(Part2, Input) {
  std::ifstream input{
      runfiles->Rlocation("_main/advent_of_code/2024/day_12_input.txt")};
  const auto [_, part_2] = Solution{input}.solve();
  ASSERT_EQ(part_2, 887932);
}
}  // namespace

int main(int argc, char *argv[]) {
  runfiles = ::bazel::tools::cpp::runfiles::Runfiles::Create(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners &listeners =
      ::testing::UnitTest::GetInstance()->listeners();
  delete listeners.Release(listeners.default_result_printer());
  assert(RUN_ALL_TESTS() == 0);
  const auto [part_1, part_2] = Solution{std::cin}.solve();
  std::cout << part_1 << '\n' << part_2 << '\n';
  return 0;
}
