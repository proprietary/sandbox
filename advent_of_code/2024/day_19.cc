#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "tools/cpp/runfiles/runfiles.h"

namespace {
using Input =
    std::pair<std::unordered_set<std::string>, std::vector<std::string>>;

auto parse(std::istream& is) -> Input {
  std::unordered_set<std::string> towels;
  std::vector<std::string> designs;
  std::string line;
  while (std::getline(is, line)) {
    if (line.empty()) {
      break;
    }
    for (auto it = line.begin(); it != line.end();) {
      auto comma = std::find(it, line.end(), ',');
      towels.emplace(it, comma);
      if (comma != line.end()) {
        comma += 2;
      }
      it = comma;
    }
  }
  while (std::getline(is, line)) {
    designs.push_back(line);
  }
  return {towels, designs};
}

class Solution {
  Input inp;
  std::unordered_map<std::string_view, uint64_t> memo;

  auto count(std::string_view design) -> __int128 {
    if (design.empty()) {
      return 1;
    }
    if (memo.contains(design)) {
      return memo[design];
    }
    __int128 res = 0;
    for (const auto& towel : inp.first) {
      if (design.starts_with(towel)) {
        std::string_view rst = design.substr(towel.length());
        res += count(rst);
      }
    }
    memo[design] = res;
    return memo[design];
  }

  public:
  Solution(std::istream& is) { inp = parse(is); }

  auto solve_part_1() -> uint64_t {
    int possible = 0;
    for (const auto& design : inp.second) {
      const auto c = count(design);
      if (c > 0) {
        ++possible;
      }
    }
    return possible;
  }

  auto solve_part_2() -> __int128 {
    __int128 ways = 0;
    for (const auto& design : inp.second) {
      ways += count(design);
    }
    return ways;
  }
};

std::string EXAMPLE = R"(r, wr, b, g, bwu, rb, gb, br

brwrr
bggr
gbbr
rrbgbr
ubwu
bwurrg
brgr
bbrgwb)";

static ::bazel::tools::cpp::runfiles::Runfiles* runfiles;
static std::string INPUT_FILE{"_main/advent_of_code/2024/day_19_input.txt"};

TEST(Part1, Example) {
  std::istringstream input{EXAMPLE};
  ASSERT_EQ(6, Solution{input}.solve_part_1());
}

TEST(Part1, Input) {
  std::ifstream input{runfiles->Rlocation(INPUT_FILE)};
  ASSERT_EQ(213, Solution{input}.solve_part_1());
}

TEST(Part2, Example) {
  std::istringstream input{EXAMPLE};
  ASSERT_EQ(16, Solution{input}.solve_part_2());
}

TEST(Part2, Input) {
  std::ifstream input{runfiles->Rlocation(INPUT_FILE)};
  ASSERT_EQ(1016700771200474, Solution{input}.solve_part_2());
}
}  // namespace

int main(int argc, char* argv[], char* envp[]) {
  runfiles = ::bazel::tools::cpp::runfiles::Runfiles::Create(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
  delete listeners.Release(listeners.default_result_printer());
  assert(!RUN_ALL_TESTS());
  fmt::println("{}", Solution{std::cin}.solve_part_1());
  fmt::println("{}", Solution{std::cin}.solve_part_2());
  return 0;
}
