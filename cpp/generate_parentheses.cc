/*
 * Leetcode Problem 22. Generate Parentheses
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 * For example, given n = 3, a solution set is:
 *
 * [
 *   "((()))",
 *   "(()())",
 *   "(())()",
 *   "()(())",
 *   "()()()"
 * ]
 */

#include <sstream>
#include <string>
#include <vector>
// following headers not required for leetcode submission:
#include <cassert>
#include <iostream>
#include <utility>

/**
 * Brute force but speed up by representing the parens as a bitset
 * "((()))" => 000111
 * "(()())" => 001011
 * Its validity can be checked in integer form. The next one can be retrieved by
 * incrementing an integer, not by shuffling strings around.
 */
class Solution {
 public:
  enum class Paren {
    OPEN = 0,
    CLOSE = 1,
  };

  /// Decode from integer (bitset) representation to a string of parens
  static std::string from_binary(unsigned int src, int width) {
    std::stringstream builder;
    while (src > 0) {
      Paren which = static_cast<Paren>(src & 1);
      switch (which) {
        case Paren::OPEN:
          builder << "(";
          break;
        case Paren::CLOSE:
          builder << ")";
          break;
      }
      src >>= 1;
      --width;
    }
    for (; width > 0; --width) {
      builder << "(";
    }
    auto s = builder.str();
    std::reverse(s.begin(), s.end());
    return s;
  }

  /// Determine if the bitset `src` with `n` paren pairs is a valid sequence of
  /// parens
  static bool check(unsigned int src, int n) {
    // least significand must be a close paren
    if (static_cast<Paren>(src & 1) != Paren::CLOSE) {
      return false;
    }
    int close_parens = 1;
    // start from the left to find a violation of the ordering of parens
    src >>= 1;  // account for the first paren being a close paren
    for (int open_parens = 0; src > 0; src >>= 1) {
      switch (static_cast<Paren>(src & 1)) {
        case Paren::OPEN:
          ++open_parens;
          break;
        case Paren::CLOSE:
          ++close_parens;
          break;
      }
      if (open_parens > close_parens) {
        return false;
      }
    }
    return close_parens == n;
  }

  std::vector<std::string> generateParenthesis(int n) {
    std::vector<std::string> out{};
    const int width = n * 2;
    // initialize bitset such that the lower half are all on i.e. representing
    // close parens
    unsigned int b = 0;
    for (int i = 0; i < n; ++i) {
      b |= (1 << i);
    }
    // last string is always alternating open/close parens like...
    // ()()()
    unsigned int last = 0;
    for (int i = 0; i < width; i += 2) {
      last |= (1 << i);
    }
    // generate strings
    for (; b <= last; ++b) {
      if (check(b, n)) {
        out.emplace_back(from_binary(b, width));
      }
    }
    return out;
  }
};

//
// the following is not required for leetcode submission
//

template <typename T>
void display(std::vector<T> src) {
  for (const auto& x : src) {
    std::cout << x << ", ";
  }
  std::cout << std::endl;
}

int main(int, char**) {
  std::vector<std::pair<int, std::vector<std::string>>> test_cases = {
      {4,
       {"(((())))", "((()()))", "((())())", "((()))()", "(()(()))", "(()()())",
        "(()())()", "(())(())", "(())()()", "()((()))", "()(()())", "()(())()",
        "()()(())", "()()()()"}},
      {3, {"((()))", "(()())", "(())()", "()(())", "()()()"}},
      {2, {"(())", "()()"}},
  };
  auto show_diff = [](auto actual, auto expected) -> void {
    std::cout << "Actual:" << std::endl;
    display(actual);
    std::cout << "Expected: " << std::endl;
    display(expected);
  };
  Solution solution{};
  for (const auto& [input, expected] : test_cases) {
    std::cout << "Testing " << input << "..." << std::endl;
    auto actual = solution.generateParenthesis(input);
    if (actual.size() != expected.size()) {
      show_diff(actual, expected);
    }
    assert(actual.size() == expected.size());
    for (int i = 0; i < actual.size(); ++i) {
      if (expected[i] != actual[i]) {
        show_diff(actual, expected);
      }
      assert(expected[i] == actual[i]);
    }
  }
  return EXIT_SUCCESS;
}
