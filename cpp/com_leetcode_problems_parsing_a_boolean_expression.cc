#include <gtest/gtest.h>

#include <cassert>
#include <stack>
#include <string>
#include <string_view>

namespace {
class Solution {
  std::string_view expr_;

  std::vector<bool> group() {
    std::vector<bool> out;
    while (!expr_.empty()) {
      switch (expr_.front()) {
        case ')':
          expr_ = expr_.substr(1);
          return out;
        case 't':
          out.push_back(true);
          expr_ = expr_.substr(1);
          break;
        case 'f':
          out.push_back(false);
          expr_ = expr_.substr(1);
          break;
        case ',':
          expr_ = expr_.substr(1);
          break;
        case '|':
        case '!':
        case '&':
          out.push_back(clause());
          break;
        default:
          assert(false);
      }
    }
    assert(false);
  }

  bool clause() {
    while (!expr_.empty()) {
      switch (expr_.front()) {
        case 't':
          return true;
        case 'f':
          return false;
        case '|': {
          expr_ = expr_.substr(2);
          const auto g = group();
          bool b = g.front();
          for (auto it = g.begin() + 1; it != g.end(); ++it) {
            b = b || *it;
          }
          return b;
        }
        case '&': {
          expr_ = expr_.substr(2);
          const auto g = group();
          bool b = g.front();
          for (auto it = g.begin() + 1; it != g.end(); ++it) {
            b = b && *it;
          }
          return b;
        }
        case '!': {
          expr_ = expr_.substr(2);
          const auto g = group();
          return !g[0];
        }
        default:
          assert(false);
      }
    }
    assert(false);
  }

  public:
  bool parseBoolExpr(std::string expression) {
    expr_ = expression;
    return clause();
  }

  bool iterative(std::string expression) {
    if (expression.length() == 1) {
      return expression.front() == 't';
    }
    std::stack<char> s;
    for (auto c = expression.rbegin(); c != expression.rend(); ++c) {
      switch (*c) {
        case ',':
        case '(':
          break;
        case ')':
          s.push(*c);
          break;
        case 'f':
        case 't':
          s.push(*c);
          break;
        case '|': {
          bool b = s.top() == 't';
          s.pop();
          while (s.top() != ')') {
            b = b || (s.top() == 't');
            s.pop();
          }
          s.pop();  // remove ')'
          s.push(b ? 't' : 'f');
          break;
        }
        case '&': {
          bool b = s.top() == 't';
          s.pop();
          while (s.top() != ')') {
            b = b && (s.top() == 't');
            s.pop();
          }
          s.pop();  // remove ')'
          s.push(b ? 't' : 'f');
          break;
        }
        case '!': {
          bool b = !(s.top() == 't');
          s.pop();
          s.pop();  // remove ')'
          s.push(b ? 't' : 'f');
          break;
        }
        default:
          assert(false);
      }
    }
    return s.top() == 't';
  }
};

struct TV {
  std::string expression;
  bool expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().parseBoolExpr(tv.expression);
  EXPECT_EQ(tv.expected, actual);
}

TEST_P(ParamTest, Iterative) {
  auto tv = GetParam();

  auto actual = Solution().iterative(tv.expression);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{"&(|(f))", false},  TV{"|(f,f,f,t)", true},
    TV{"!(&(f,t))", true}, TV{"|(&(t,f,t),t)", true},
    TV{"&(t,f)", false},   TV{"|(&(t,f,t),!(t))", false},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
