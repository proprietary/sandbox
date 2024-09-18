/**
 * Leetcode 43. Multiply Strings
 * Given two non-negative integers num1 and num2 represented as strings, return
 * the product of num1 and num2, also represented as a string.
 *
 * Example 1:
 *
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 *
 * Example 2:
 *
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 *
 * Note:
 *
 *     The length of both num1 and num2 is < 110.
 *     Both num1 and num2 contain only digits 0-9.
 *     Both num1 and num2 do not contain any leading zero, except the number 0
 * itself. You must not use any built-in BigInteger library or convert the
 * inputs to integer directly.
 *
 */
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<int> split_num_string(const std::string& s) {
  std::vector<int> out{};
  const auto sz = s.size();
  out.reserve(sz);
  for (size_t i = 0; i < sz; ++i) {
    int v = static_cast<int>(s[i] - '0');
    out.push_back(v);
  }
  return out;
}

std::string merge_nums(const std::vector<int>& nums) {
  std::stringstream ss{};
  for (auto i : nums) {
    ss << i;
  }
  return ss.str();
}

int add(std::vector<int>& out, const std::vector<std::vector<int>>& v) {
  out.clear();
  {
    auto& largest = *std::max_element(v.begin(), v.end(),
                                      [](const auto& a, const auto& b) -> bool {
                                        return a.size() < b.size();
                                      });
    out.resize(largest.size());
  }
  std::fill(out.begin(), out.end(), 0);
  for (auto it = v.begin(); it != v.end(); ++it) {
    const auto& b = *it;
    assert(out.size() >= b.size());
    int carry = 0;
    int out_idx = out.size() - 1;
    int b_idx = b.size() - 1;
    for (; b_idx >= 0 && out_idx >= 0; --b_idx, --out_idx) {
      auto v = out[out_idx] + b[b_idx] + carry;
      out[out_idx] = v % 10;
      carry = v / 10;
    }
    if (carry > 0) {
      if (out_idx < 0) {
        out.insert(out.begin(), carry);
      } else {
        out[out_idx] += carry;
      }
    }
  }
  return 1;
}

int mul(std::vector<int>& out, const std::vector<int>& a,
        const std::vector<int>& b) {
  std::vector<std::vector<int>> nums;
  int index = 0;
  for (auto m = a.rbegin(); m != a.rend(); ++m) {
    int carry = 0;
    std::vector<int> this_nums{};
    this_nums.resize(index);
    std::fill(this_nums.begin(), this_nums.end(), 0);
    for (auto n = b.rbegin(); n != b.rend(); ++n) {
      int val = (*n * *m) + carry;
      carry = val / 10;
      this_nums.push_back(val % 10);
    }
    if (carry > 0) {
      this_nums.push_back(carry);
    }
    ++index;
    std::reverse(this_nums.begin(), this_nums.end());
    nums.emplace_back(std::move(this_nums));
  }
  auto res = add(out, nums);
  // remove leading zeros
  auto leading_zeros_end = out.begin();
  while (leading_zeros_end != out.end() && *leading_zeros_end == 0) {
    ++leading_zeros_end;
  }
  if (leading_zeros_end != out.begin()) {
    out.erase(out.begin(), leading_zeros_end);
  }
  if (out.size() == 0) {
    out.push_back(0);
  }
  return res;
}

class Solution {
  public:
  std::string multiply(std::string num1, std::string num2) {
    const auto s1 = split_num_string(num1);
    const auto s2 = split_num_string(num2);
    std::vector<int> nums{};
    auto res = mul(nums, s1, s2);
    assert(res != 0);
    return merge_nums(nums);
  }
};

TEST(Leetcode, TestGivenExamples) {
  Solution s{};
  auto res = s.multiply("2", "3");
  EXPECT_STREQ("6", res.c_str());
  res = s.multiply("123", "456");
  EXPECT_STREQ("56088", res.c_str());
  res = s.multiply("999", "999");
  EXPECT_STREQ("998001", res.c_str());
  res = s.multiply("9133", "0");
  EXPECT_STREQ("0", res.c_str());
  res = s.multiply("123456789", "987654321");
  EXPECT_STREQ("121932631112635269", res.c_str());
}
