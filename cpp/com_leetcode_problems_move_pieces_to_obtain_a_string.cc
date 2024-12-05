#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace {
inline bool nonblank(const char ch) { return ch != '_'; }
class Solution {
  public:
  bool canChange(std::string start, std::string target) {
    auto s = start.begin();
    auto t = target.begin();
    do {
      s = std::find_if(s, start.end(), nonblank);
      t = std::find_if(t, target.end(), nonblank);
      if (s == start.end() && t == target.end()) {
        return true;
      }
      if ((s == start.end()) != (t == target.end()) || *t != *s) {
        return false;
      }
      const auto s_index = s - start.begin();
      const auto t_index = t - target.begin();
      if (s_index != t_index) {
        if (s_index < t_index && *s != 'R') {
          return false;
        }
        if (s_index > t_index && *s != 'L') {
          return false;
        }
      }
      s++;
      t++;
    } while (s != start.end() && t != target.end());
    s = std::find_if(s, start.end(), nonblank);
    t = std::find_if(t, target.end(), nonblank);
    return s == start.end() && t == target.end();
  }
};

struct TV {
  std::string start;
  std::string target;
  bool expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().canChange(tv.start, tv.target);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{"_L__R__R_", "L______RR", true},
    TV{"R_L_", "__LR", false},
    TV{"_R", "R_", false},
    TV{"__", "__", true},
    TV{"_L", "LL", false},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
