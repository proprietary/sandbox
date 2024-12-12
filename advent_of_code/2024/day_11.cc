#include <gtest/gtest.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "tools/cpp/runfiles/runfiles.h"

namespace {

auto parse(std::istream& is) -> std::vector<uint64_t> {
  std::string line;
  std::getline(is, line);
  std::istringstream iss{line};
  std::string n;
  std::vector<uint64_t> res;
  while (iss >> n) {
    res.push_back(std::stoull(n));
  }
  return res;
}

auto to_digits(uint64_t n) -> std::vector<uint64_t> {
  std::vector<uint64_t> digits;
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
  std::ranges::reverse(digits);
  return digits;
}

auto split(const std::vector<uint64_t>& digits)
    -> std::pair<uint64_t, uint64_t> {
  uint64_t lhs = 0, rhs = 0;
  int i = 0;
  for (; i < digits.size() / 2; ++i) {
    lhs = (lhs * 10) + digits[i];
  }
  for (; i < digits.size(); ++i) {
    rhs = (rhs * 10) + digits[i];
  }
  return {lhs, rhs};
}

struct Arg {
  uint64_t stone;
  int blinks;

  bool operator==(const Arg& other) const {
    return other.stone == stone && other.blinks == blinks;
  }

  struct Hash {
    size_t operator()(const Arg& a) const {
      const size_t h1 = std::hash<uint64_t>{}(a.stone);
      const size_t h2 = std::hash<int>{}(a.blinks);
      return h1 ^ (h2 << 1) ^ (h2 >> 1);
    }
  };
};

uint64_t dfs(const Arg arg,
             std::unordered_map<Arg, uint64_t, Arg::Hash>& memo) {
  if (arg.blinks == 0) {
    return 1;
  }
  if (memo.contains(arg)) {
    return memo[arg];
  }
  uint64_t res = 0;
  if (arg.stone == 0) {
    res = dfs(Arg{1, arg.blinks - 1}, memo);
  } else if (const auto digits = to_digits(arg.stone); digits.size() % 2 == 0) {
    const auto [lhs, rhs] = split(digits);
    res += dfs(Arg{lhs, arg.blinks - 1}, memo);
    res += dfs(Arg{rhs, arg.blinks - 1}, memo);
  } else {
    res = dfs(Arg{arg.stone * 2024, arg.blinks - 1}, memo);
  }
  memo[arg] = res;
  return res;
}

uint64_t count_after_blinks(const std::vector<uint64_t>& stones,
                            const int blinks) {
  std::unordered_map<Arg, uint64_t, Arg::Hash> memo;
  uint64_t res = 0;
  for (const uint64_t stone : stones) {
    const Arg arg{stone, blinks};
    res += dfs(arg, memo);
  }
  return res;
}

bazel::tools::cpp::runfiles::Runfiles* runfiles;

constexpr std::string EXAMPLE = "125 17";

TEST(Part1, Blinks) {
  std::istringstream input{EXAMPLE};
  const auto stones = parse(input);
  ASSERT_EQ(count_after_blinks(stones, 1), 3);
  ASSERT_EQ(count_after_blinks(stones, 2), 4);
  ASSERT_EQ(count_after_blinks(stones, 3), 5);
  ASSERT_EQ(count_after_blinks(stones, 4), 9);
  ASSERT_EQ(count_after_blinks(stones, 6), 22);
  ASSERT_EQ(count_after_blinks(stones, 25), 55312);
}

TEST(AoC, Input) {
  std::ifstream f{
      runfiles->Rlocation("_main/advent_of_code/2024/day_11_input.txt")};
  const auto stones = parse(f);
  ASSERT_EQ(count_after_blinks(stones, 25), 172484);
  ASSERT_EQ(count_after_blinks(stones, 75), 205913561055242);
}

}  // namespace

int main(int argc, char* argv[]) {
  std::string error;
  runfiles = bazel::tools::cpp::runfiles::Runfiles::Create(argv[0], &error);
  assert(runfiles);
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners& listeners =
      testing::UnitTest::GetInstance()->listeners();
  delete listeners.Release(listeners.default_result_printer());
  assert(RUN_ALL_TESTS() == 0);
  auto stones = parse(std::cin);
  std::cout << count_after_blinks(stones, 25) << '\n';
  std::cout << count_after_blinks(stones, 75) << '\n';
  return 0;
}
