#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "tools/cpp/runfiles/runfiles.h"

namespace {
struct Button {
  int64_t x;
  int64_t y;
};

struct Prize {
  int64_t x;
  int64_t y;
};

struct ClawMachine {
  std::array<Button, 2> buttons;
  Prize prize;
};

auto parse(std::istream& is) -> std::vector<ClawMachine> {
  std::vector<ClawMachine> claw_machines;
  std::string line;
  std::regex button_pattern{R"(Button ([AB]): X\+(\d+), Y\+(\d+))"};
  std::regex prize_pattern{R"(Prize: X=(\d+), Y=(\d+))"};
  ClawMachine temp;
  while (std::getline(is, line)) {
    if (line.empty()) {
      claw_machines.push_back(temp);
      temp = ClawMachine{};
      continue;
    }
    std::smatch matches;
    if (std::regex_match(line, matches, button_pattern)) {
      const int64_t x = std::stoull(matches[2].str());
      const int64_t y = std::stoull(matches[3].str());
      if (matches[1].str() == "A") {
        temp.buttons[0] = Button{.x = x, .y = y};
      } else if (matches[1].str() == "B") {
        temp.buttons[1] = Button{.x = x, .y = y};
      } else {
        assert(false);
      }
    } else if (std::regex_match(line, matches, prize_pattern)) {
      temp.prize.x = std::stoull(matches[1].str());
      temp.prize.y = std::stoull(matches[2].str());
    }
  }
  claw_machines.push_back(temp);
  return claw_machines;
}

auto cramers_rule(const ClawMachine& c) -> std::tuple<int64_t, int64_t, bool> {
  // A * button[0].x + B * button[1].x = prize.x
  const int64_t& eq1_a = c.buttons[0].x;
  const int64_t& eq1_b = c.buttons[1].x;
  const int64_t& eq1_c = c.prize.x;
  // A * button[0].y + B * button[1].y = prize.y
  const int64_t& eq2_a = c.buttons[0].y;
  const int64_t& eq2_b = c.buttons[1].y;
  const int64_t& eq2_c = c.prize.y;
  const int64_t d1 = eq1_a * eq2_b;
  const int64_t d2 = eq2_a * eq1_b;
  if (d1 == d2) {
    return {0, 0, false};
  }
  const int64_t d = d1 - d2;
  const int64_t delta_x = eq1_c * eq2_b - eq2_c * eq1_b;
  const int64_t delta_y = eq1_a * eq2_c - eq2_a * eq1_c;
  const int64_t x = delta_x / d;
  const int64_t y = delta_y / d;
  return {x, y, true};
}

auto solve(std::istream& is) -> std::pair<int64_t, int64_t> {
  auto claw_machines = parse(is);
  int64_t part_1 = 0, part_2 = 0;
  for (const auto& c : claw_machines) {
    const auto [a, b, ok] = cramers_rule(c);
    const bool valid = ok &&
                       c.buttons[0].x * a + c.buttons[1].x * b == c.prize.x &&
                       c.buttons[0].y * a + c.buttons[1].y * b == c.prize.y;
    if (valid) {
      part_1 += 3 * a + b;
    }
  }
  const int64_t shift = 10000000000000;
  for (auto& c : claw_machines) {
    c.prize.x += shift;
    c.prize.y += shift;
    const auto [a, b, ok] = cramers_rule(c);
    const bool valid = ok &&
                       c.buttons[0].x * a + c.buttons[1].x * b == c.prize.x &&
                       c.buttons[0].y * a + c.buttons[1].y * b == c.prize.y;
    if (valid) {
      part_2 += 3 * a + b;
    }
  }
  return {part_1, part_2};
}

std::string EXAMPLE = R"(Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279)";

::bazel::tools::cpp::runfiles::Runfiles* runfiles;

std::string INPUT_FILE = "_main/advent_of_code/2024/day_13_input.txt";

TEST(Parse, CanReconstructOriginal) {
  std::istringstream input{EXAMPLE};
  const auto parsed = parse(input);
  std::ostringstream reconstructed;
  for (const auto& claw_machine : parsed) {
    reconstructed << "Button A: X+" << claw_machine.buttons[0].x << ", Y+"
                  << claw_machine.buttons[0].y << '\n'
                  << "Button B: X+" << claw_machine.buttons[1].x << ", Y+"
                  << claw_machine.buttons[1].y << '\n'
                  << "Prize: X=" << claw_machine.prize.x
                  << ", Y=" << claw_machine.prize.y << "\n\n";
  }
  const auto s = reconstructed.str();
  ASSERT_EQ(EXAMPLE, s.substr(0, s.length() - 2));
}

TEST(Part1, Example) {
  std::istringstream input{EXAMPLE};
  const auto [part_1, _] = solve(input);
  ASSERT_EQ(part_1, 480);
}

TEST(Part1, Input) {
  std::fstream input{runfiles->Rlocation(INPUT_FILE)};
  const auto [part_1, _] = solve(input);
  ASSERT_EQ(part_1, 25629);
}

TEST(Part2, Input) {
  std::fstream input{runfiles->Rlocation(INPUT_FILE)};
  const auto [_, part_2] = solve(input);
  ASSERT_EQ(part_2, 107487112929999);
}

}  // namespace

int main(int argc, char* argv[]) {
  runfiles = ::bazel::tools::cpp::runfiles::Runfiles::Create(argv[0]);
  assert(runfiles);
  // ::testing::InitGoogleTest(&argc, argv);
  // auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
  // delete listeners.Release(listeners.default_result_printer());
  // assert(!RUN_ALL_TESTS());
  const auto [part_1, part_2] = solve(std::cin);
  fmt::println("{}\n{}", part_1, part_2);
  return 0;
}
