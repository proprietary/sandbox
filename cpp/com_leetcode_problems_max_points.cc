#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

class Solution {
  public:
  inline double slope(const std::vector<int>& a, const std::vector<int>& b) {
    return static_cast<double>(b[1] - a[1]) / static_cast<double>(b[0] - a[0]);
  }
  int maxPoints(std::vector<std::vector<int>>& points) {
    std::sort(points.begin(), points.end());
    int best = 1;
    for (int i = 0; i < points.size(); i++) {
      for (int j = i + 1; j < points.size(); j++) {
        const double s1 = slope(points[i], points[j]);
        int points_on_line = 2;
        for (int k = j + 1; k < points.size(); k++) {
          const auto s2 = slope(points[j], points[k]);
          if (s2 == s1) {
            points_on_line++;
          }
        }
        best = std::max(best, points_on_line);
      }
    }
    return best;
  }
};

struct TestVec {
  std::vector<std::vector<int>> points;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, minSteps) {
  auto tv = GetParam();

  const int actual = Solution().maxPoints(tv.points);

  EXPECT_EQ(actual, tv.expected);
}

static const auto TEST_CASES = ::testing::Values(
    TestVec{{{1, 1}, {2, 2}, {3, 3}}, 3},
    TestVec{{{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}, 4},
    TestVec{.points = {{0, 0}}, .expected = 1});

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
