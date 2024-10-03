#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "test_case_helper.hpp"

class Trie {
  static constexpr size_t kAlphabetSize = 10;
  class TrieNode {
public:
    std::array<std::unique_ptr<TrieNode>, kAlphabetSize> children;
    bool is_end = false;
  };
  std::unique_ptr<TrieNode> root_;

  int longestCommonPrefix(TrieNode* t1, TrieNode* t2, int length) {
    if (t1 == nullptr || t2 == nullptr) return length;
    int best = length;
    for (auto i = 0; i < kAlphabetSize; i++) {
      if (t1->children[i] && t2->children[i]) {
        best = std::max(best,
                        longestCommonPrefix(t1->children[i].get(),
                                            t2->children[i].get(), length + 1));
      }
    }
    return best;
  }

  public:
  Trie() : root_(std::make_unique<TrieNode>()) {}

  template <typename It>
  void insert(It begin, It end) {
    auto cur = root_.get();
    for (auto it = begin; it != end; it++) {
      if (!cur->children[*it]) {
        cur->children[*it] = std::make_unique<TrieNode>();
      }
      cur = cur->children[*it].get();
    }
    cur->is_end = true;
  }

  int longestCommonPrefix(const Trie& other) {
    return longestCommonPrefix(root_.get(), other.root_.get(), 0);
  }
};

class Solution {
  std::vector<int8_t> digits_buf_;

  auto to_digits(int n) -> const std::vector<int8_t>& {
    digits_buf_.clear();
    do {
      digits_buf_.push_back(n % 10);
      n /= 10;
    } while (n > 0);
    std::reverse(digits_buf_.begin(), digits_buf_.end());
    return digits_buf_;
  }

  public:
  int longestCommonPrefixBruteForce(std::vector<int>& arr1,
                                    std::vector<int>& arr2) {
    int longest = -1;
    for (auto it1 = arr1.begin(); it1 != arr1.end(); it1++) {
      const auto d1 = to_digits(*it1);
      for (auto it2 = arr2.begin(); it2 != arr2.end(); it2++) {
        const auto d2 = to_digits(*it2);
        int in_common = 0;
        for (int i = 0; i < std::min(d1.size(), d2.size()) && d1[i] == d2[i];
             i++) {
          in_common++;
        }
        longest = std::max(longest, in_common);
      }
    }
    return longest;
  }

  int longestCommonPrefix(std::vector<int>& arr1, std::vector<int>& arr2) {
    Trie t1;
    std::ranges::for_each(arr1, [&t1, this](const auto n) {
      const auto digits = to_digits(n);
      t1.insert(digits.begin(), digits.end());
    });
    Trie t2;
    std::ranges::for_each(arr2, [&t2, this](const auto n) {
      const auto digits = to_digits(n);
      t2.insert(digits.begin(), digits.end());
    });
    return t1.longestCommonPrefix(t2);
  }
};

struct TestVec {
  std::vector<int> arr1;
  std::vector<int> arr2;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, ExampleBruteForce) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected,
            Solution().longestCommonPrefixBruteForce(tv.arr1, tv.arr2));
}

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected, Solution().longestCommonPrefix(tv.arr1, tv.arr2));
}

auto parse_test_cases() -> std::vector<TestVec> {
  static constexpr std::string_view raw =
      R"(
[1,10,100]
[1000]
3
[1,2,3]
[4,4,4]
0
)";
  std::vector<TestVec> test_cases;
  for (auto c : partition_test_cases(raw, 3)) {
    test_cases.emplace_back(TestVec{.arr1 = IntVecParser(c[0]).parse(),
                                    .arr2 = IntVecParser(c[1]).parse(),
                                    .expected = std::stoi(c[2])});
  }
  return test_cases;
}

static auto cases = parse_test_cases();
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
