#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "tools/cpp/runfiles/runfiles.h"

namespace {
::bazel::tools::cpp::runfiles::Runfiles* runfiles;

std::string INPUT_FILE{"_main/advent_of_code/2024/day_14_input.txt"};

std::string EXAMPLE = R"(p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3)";

struct Point {
  int x;
  int y;
};

struct Robot {
  Point pos;
  Point velocity;
};

auto parse(std::istream& input) -> std::vector<Robot> {
  std::vector<Robot> res;
  std::regex robot_pattern{R"(p=(\d+),(\d+) v=(-?[\d]+),(-?[\d]+))"};
  std::string line;
  std::smatch matches;
  while (std::getline(input, line)) {
    assert(std::regex_match(line, matches, robot_pattern));
    res.emplace_back();
    auto& robot = res.back();
    robot.pos.x = std::stoi(matches[1].str());
    robot.pos.y = std::stoi(matches[2].str());
    robot.velocity.x = std::stoi(matches[3].str());
    robot.velocity.y = std::stoi(matches[4].str());
  }
  return res;
}

void sim(std::vector<Robot>& m, int seconds, const int width = 101,
         const int height = 103) {
  while (seconds-- > 0) {
    for (Robot& robot : m) {
      robot.pos.x += robot.velocity.x;
      robot.pos.y += robot.velocity.y;
      if (robot.pos.x < 0) {
        robot.pos.x += width;
      }
      if (robot.pos.x >= width) {
        robot.pos.x -= width;
      }
      if (robot.pos.y < 0) {
        robot.pos.y += height;
      }
      if (robot.pos.y >= height) {
        robot.pos.y -= height;
      }
    }
  }
}

auto solve_part_1(std::vector<Robot> robots) -> int {
  const int width = 101;
  const int height = 103;
  sim(robots, 100, width, height);
  const int q1 = std::ranges::count_if(
      robots, [&width, &height](const auto& robot) -> bool {
        return robot.pos.x < width / 2 && robot.pos.y < height / 2;
      });
  const int q2 = std::ranges::count_if(
      robots, [&width, &height](const auto& robot) -> bool {
        return robot.pos.x > width / 2 && robot.pos.y < height / 2;
      });
  const int q3 = std::ranges::count_if(
      robots, [&width, &height](const auto& robot) -> bool {
        return robot.pos.x < width / 2 && robot.pos.y > height / 2;
      });
  const int q4 = std::ranges::count_if(
      robots, [&width, &height](const auto& robot) -> bool {
        return robot.pos.x > width / 2 && robot.pos.y > height / 2;
      });
  return q1 * q2 * q3 * q4;
}

auto solve_part_2(std::vector<Robot> robots) -> int {
  constexpr int width = 101;
  constexpr int height = 103;
  std::array<std::array<bool, width>, height> map;
  std::array<std::array<int, 2>, 4> directions = {
      std::array<int, 2>{-1, 0},
      std::array<int, 2>{1, 0},
      std::array<int, 2>{0, -1},
      std::array<int, 2>{0, 1},
  };

  int seconds = 0;

  for (; seconds < 100'000; ++seconds) {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        map[y][x] = false;
      }
    }
    for (const Robot& robot : robots) {
      map[robot.pos.y][robot.pos.x] = true;
    }
    int neighbors = 0;
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        if (map[y][x]) {
          for (const auto& direction : directions) {
            const int next_y = direction[0] + y;
            const int next_x = direction[1] + x;
            if (next_y < height && next_y >= 0 && next_x < width &&
                next_x >= 0 && map[next_y][next_x]) {
              ++neighbors;
            }
          }
        }
      }
    }
    if (neighbors > 500) break;
    sim(robots, 1, width, height);
  }
  // for (int y = 0; y < height; ++y) {
  //   for (int x = 0; x < width; ++x) {
  //     fmt::print("{}", map[y][x] ? 'X' : ' ');
  //   }
  //   fmt::print("\n");
  // }
  // fmt::print("\n");
  return seconds;
}

auto solve(std::istream& input) -> std::pair<int, int> {
  auto robots = parse(input);
  const int part_1 = solve_part_1(robots);
  const int part_2 = solve_part_2(robots);
  return {part_1, part_2};
}

TEST(Parse, Example) {
  std::istringstream input{EXAMPLE};
  const auto parsed = parse(input);
  std::ostringstream formatted;
  for (const auto& robot : parsed) {
    formatted << fmt::format("p={},{} v={},{}\n", robot.pos.x, robot.pos.y,
                             robot.velocity.x, robot.velocity.y);
  }
  std::string got = formatted.str();
  got.pop_back();
  ASSERT_EQ(EXAMPLE, got);
}

TEST(Sim, Example) {
  const std::string expected = R"(......2..1.
...........
1..........
.11........
.....1.....
...12......
.1....1....
)";
  std::istringstream input{EXAMPLE};
  auto robots = parse(input);
  const int width = 11, height = 7;
  sim(robots, 100, width, height);
  std::sort(robots.begin(), robots.end(), [](const auto& a, const auto& b) {
    return a.pos.x < b.pos.x || a.pos.y < b.pos.y;
  });
  std::ostringstream formatted;
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      const int count = std::count_if(
          robots.begin(), robots.end(), [&y, &x](const Robot& robot) -> bool {
            return robot.pos.x == x && robot.pos.y == y;
          });
      if (count == 0) {
        formatted << '.';
      } else {
        formatted << count;
      }
    }
    formatted << '\n';
  }
  ASSERT_EQ(expected, formatted.str());
}

TEST(Part1, Input) {
  std::ifstream input{runfiles->Rlocation(INPUT_FILE)};
  const auto [part_1, _] = solve(input);
  ASSERT_EQ(part_1, 224357412);
}

TEST(Part2, Input) {
  std::ifstream input{runfiles->Rlocation(INPUT_FILE)};
  const auto [_, part_2] = solve(input);
  ASSERT_EQ(part_2, 7083);
}
}  // namespace

int main(int argc, char* argv[]) {
  runfiles = ::bazel::tools::cpp::runfiles::Runfiles::Create(argv[0]);
  assert(runfiles);
  ::testing::InitGoogleTest(&argc, argv);
  auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
  delete listeners.Release(listeners.default_result_printer());
  assert(RUN_ALL_TESTS() == 0);
  const auto [part_1, part_2] = solve(std::cin);
  fmt::println("{}\n{}", part_1, part_2);
  return 0;
}
