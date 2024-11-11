#include <gtest/gtest.h>

#include <array>
#include <vector>

namespace {
template <size_t n>
constexpr auto generate_primes() -> std::array<int, n + 1> {
  std::array<int, n + 1> primes{0, 0};
  for (int i = 2; i <= n; ++i) {
    bool is_prime = true;
    for (int j = 2; j * j <= i && is_prime; ++j) {
      is_prime = (i % j) > 0;
    }
    primes[i] = is_prime ? i : primes[i - 1];
  }
  return primes;
}

class Solution {
  public:
  bool primeSubOperation(std::vector<int>& nums) {
    constexpr auto primes = generate_primes<1000>();
    int prev = 0;
    for (int n : nums) {
      const int diff = n - prev;
      if (diff <= 0) {
        return false;
      } else if (diff > 2) {
        prev = n - primes[diff - 1];
      } else {
        prev = n;
      }
    }
    return true;
  }
};

struct TV {
  std::vector<int> nums;
  bool expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().primeSubOperation(tv.nums);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{4, 9, 6, 10}, true},
    TV{{6, 8, 11, 12}, true},
    TV{{5, 8, 3}, false},
    TV{{998, 2}, true},
    TV{{3, 4, 10, 15, 6}, true},
    TV{{76,  957, 56,  158, 431, 761, 709, 699, 512, 405, 570, 422, 540,
        143, 569, 438, 117, 583, 471, 610, 388, 267, 486, 150, 628, 305,
        48,  871, 133, 325, 108, 303, 989, 25,  318, 108, 658, 838, 909,
        534, 564, 946, 218, 923, 260, 814, 874, 276, 661, 800, 277, 189,
        797, 243, 778, 856, 303, 31,  762, 509, 164, 966, 688, 796, 341,
        429, 611, 308, 181, 182, 141, 397, 52,  972, 551, 618, 138, 833,
        753, 96,  460, 154, 724, 914, 411, 851, 585, 995, 39,  449, 851,
        573, 701, 689, 963, 691, 695, 389, 870, 519},
       false},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
