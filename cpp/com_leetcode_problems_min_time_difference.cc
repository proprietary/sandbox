#include <gtest/gtest.h>

#include <algorithm>
#include <complex>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils.hpp"

class Solution {
  static constexpr int minutes_in_day = 1440;

  public:
  Solution() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }
  int findMinDifference(std::vector<std::string>& timePoints) {
    std::vector<int> points;
    points.reserve(timePoints.size());
    for (const auto& tp : timePoints) {
      const auto hours = (tp[0] - '0') * 10 + tp[1] - '0';
      const auto minutes = (tp[3] - '0') * 10 + tp[4] - '0';
      const auto total_minutes = hours * 60 + minutes;
      points.push_back(total_minutes);
    }
    std::sort(points.begin(), points.end());
    const auto n = points.size();
    int best = std::numeric_limits<int>::max();
    for (int i = 0; i < points.size(); i++) {
      int diff = std::abs(points[i] - points[(i - 1 + n) % n]);
      diff = std::min(diff, minutes_in_day - diff);
      best = std::min(best, diff);
    }
    return best;
  }
};

struct TestVec {
  std::vector<std::string> input;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, minSteps) {
  const auto& tv = GetParam();

  auto copy = tv.input;
  int actual = Solution().findMinDifference(copy);

  EXPECT_EQ(actual, tv.expected);
}

static const auto TEST_CASES = ::testing::Values(
    TestVec{{"23:59", "00:00"}, 1}, TestVec{{"00:00", "23:59", "00:00"}, 0},
    TestVec{{"05:31", "22:08", "00:35"}, 147}, TestVec{{"12:12", "00:13"}, 719},
    TestVec{{"14:49", "09:56", "01:02"}, 293});

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
