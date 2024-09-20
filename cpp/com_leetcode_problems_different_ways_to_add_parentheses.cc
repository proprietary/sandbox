#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <unordered_set>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  public:
  std::vector<int> ways(const std::string& expr, size_t left, size_t right) {
    std::vector<int> arr;
    for (auto i = left; i <= right; i++) {
      if (expr[i] == '*' || expr[i] == '-' || expr[i] == '+') {
        auto lst1 = ways(expr, left, i - 1);
        auto lst2 = ways(expr, i + 1, right);
        for (const auto n1 : lst1) {
          for (const auto n2 : lst2) {
            int res = 0;
            switch (expr[i]) {
              case '*':
                res = n1 * n2;
                break;
              case '-':
                res = n1 - n2;
                break;
              case '+':
                res = n1 + n2;
                break;
            }
            arr.push_back(res);
          }
        }
      }
    }
    if (arr.size() == 0) {
      int n = std::stoi(expr.substr(left, right + 1));
      arr.push_back(n);
    }
    return arr;
  }

  std::vector<int> diffWaysToCompute(std::string expression) {
    return ways(expression, 0, expression.length() - 1);
  }
};

int eval(const std::string& expr, size_t& begin) {
  int res = 0;
  int lhs = 0;
  int rhs = 0;
  if (expr[begin] == '(') {
    begin += 1;
    lhs = eval(expr, begin);
  } else {
    for (; begin < expr.length() && std::isdigit(expr[begin]); begin++) {
      lhs = lhs * 10 + (expr[begin] - '0');
    }
  }
  if (expr[begin] == ')') {
    begin++;
    return lhs;
  }
  if (begin >= expr.length()) {
    return lhs;
  }
  char op = expr[begin++];
  if (expr[begin] == '(') {
    begin += 1;
    rhs = eval(expr, begin);
  } else {
    for (; begin < expr.length() && std::isdigit(expr[begin]); begin++) {
      rhs = rhs * 10 + (expr[begin] - '0');
    }
  }
  if (begin < expr.length()) {
    begin++;
  }
  switch (op) {
    case '*':
      res = lhs * rhs;
      break;
    case '+':
      res = lhs + rhs;
      break;
    case '-':
      res = lhs - rhs;
      break;
  }
  return res;
}

int eval(const std::string& expr) {
  size_t i = 0;
  return eval(expr, i);
}

TEST(Support, EvalExpr) {
  EXPECT_EQ(-34, eval("(2*(3-(4*5)))"));
  EXPECT_EQ(-14, eval("((2*3)-(4*5))"));
  EXPECT_EQ(-10, eval("((2*(3-4))*5)"));
  EXPECT_EQ(-10, eval("(2*((3-4)*5))"));
  EXPECT_EQ(10, eval("(((2*3)-4)*5)"));
}

struct TestVec {
  std::string input;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, minSteps) {
  auto tv = GetParam();

  const auto actual = Solution().diffWaysToCompute(tv.input);
  std::unordered_set<int> actual_set;
  std::for_each(actual.begin(), actual.end(),
                [&actual_set](const auto x) { actual_set.insert(x); });
  std::unordered_set<int> expected_set;
  std::for_each(tv.expected.begin(), tv.expected.end(),
                [&expected_set](const auto x) { expected_set.insert(x); });

  EXPECT_EQ(actual_set, expected_set);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
"2-1-1"
[0,2]
"2*3-4*5"
[-34,-14,-10,-10,10]
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 2);
  for (auto c : cases) {
    tvs.push_back(TestVec{.input = c[0].substr(1, c[0].length() - 1),
                          .expected = IntVecParser(c[1]).parse()});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
