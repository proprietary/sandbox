#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

namespace {
class Solution {
  public:
  long long maxMatrixSum(std::vector<std::vector<int>>& matrix) {
    const int n = matrix.size();
    int smallest = std::numeric_limits<int>::max();
    int negatives = 0;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        const int a = std::abs(matrix[i][j]);
        if (matrix[i][j] < 0) {
          ++negatives;
        }
        smallest = std::min(smallest, a);
        sum += a;
      }
    }
    if (negatives % 2 > 0) {
      sum -= smallest * 2;
    }
    return sum;
  }
};

struct TV {
  std::vector<std::vector<int>> matrix;
  long long expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().maxMatrixSum(tv.matrix);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{{1, -1}, {-1, 1}}, 4},
    TV{{{1, 2, 3}, {-1, -2, -3}, {1, 2, 3}}, 16},
    TV{{{-1, 0, -1}, {-2, 1, 3}, {3, 2, 2}}, 15},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
