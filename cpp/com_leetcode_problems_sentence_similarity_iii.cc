#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  static auto split(std::string_view s, char delim = ' ')
      -> std::vector<std::string_view> {
    std::vector<std::string_view> res;
    auto it = s.begin();
    auto p = it;
    while (it != s.end()) {
      if (*it == delim) {
        res.emplace_back(p, it);
        p = it + 1;
      }
      it++;
    }
    if (p != it) {
      res.emplace_back(p, it);
    }
    return res;
  }

  public:
  bool areSentencesSimilar(std::string sentence1, std::string sentence2) {
    const auto s1 = split(sentence1);
    const auto s2 = split(sentence2);
    const auto& shorter = s1.size() <= s2.size() ? s1 : s2;
    const auto& longer = &shorter == &s1 ? s2 : s1;
    const auto len_diff = longer.size() - shorter.size();
    int64_t left = 0;
    for (; left < shorter.size(); left++) {
      if (shorter[left] != longer[left]) {
        break;
      }
    }
    if (left == shorter.size()) return true;
    int64_t right = longer.size() - 1;
    for (int64_t i = shorter.size() - 1; i >= left && right >= left;
         i--, right--) {
      if (shorter[i] != longer[right]) {
        break;
      }
    }
    return right - left + 1 == len_diff;
  }
};

struct TestVec {
  std::string sentence1;
  std::string sentence2;
  bool expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected,
            Solution().areSentencesSimilar(tv.sentence1, tv.sentence2));
}

auto parse_test_cases() -> std::vector<TestVec> {
  static constexpr std::string_view raw =
      R"(
My name is Haley
My Haley
true
of
A lot of words
false
Eating right now
Eating
true
Ogn WtWj HneS
Ogn WtWj HneS
true
A A AAa
A AAa
true
A B C D B B
A B B
true
)";
  std::vector<TestVec> test_cases;
  for (auto c : partition_test_cases(raw, 3)) {
    test_cases.emplace_back(TestVec{.sentence1 = c[0],
                                    .sentence2 = c[1],
                                    .expected = c[2] == "true" ? true : false});
  }
  return test_cases;
}

static auto cases = parse_test_cases();
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
