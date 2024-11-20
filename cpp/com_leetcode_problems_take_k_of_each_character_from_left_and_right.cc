#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <ranges>
#include <string>

namespace {
class Solution {
  public:
  int takeCharacters(std::string s, int k) {
    const int n = s.length();
    std::array<int, 3> frequency{0, 0, 0};
    for (const auto ch : s) {
      frequency[ch - 'a']++;
    }
    if (*std::ranges::min_element(frequency) < k) {
      return -1;
    }

    int best = 0;
    std::array<int, 3> window{0, 0, 0};
    auto l = s.begin();
    for (auto r = s.begin(); r != s.end(); ++r) {
      window[*r - 'a']++;
      while (l <= r &&
             std::ranges::any_of(std::views::iota(0, 3),
                                 [&window, &frequency, &k](const auto idx) {
                                   return frequency[idx] - window[idx] < k;
                                 })) {
        window[*(l++) - 'a']--;
      }
      best = std::max(best, static_cast<int>(r - l + 1));
    }
    return n - best;
  }
};

struct TV {
  std::string s;
  int k;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().takeCharacters(tv.s, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{"aabaaaacaabc", 2, 8},
    TV{"a", 1, -1},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
