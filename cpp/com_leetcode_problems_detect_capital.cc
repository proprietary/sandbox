// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

// Given a word, you need to judge whether the usage of capitals in it is right
// or not.

// We define the usage of capitals in a word to be right when one of the
// following cases holds:

// All letters in this word are capitals, like "USA".
// All letters in this word are not capitals, like "leetcode".
// Only the first letter in this word is capital, like "Google".
// Otherwise, we define that this word doesn't use capitals in a right way.

// Example 1:

// Input: "USA"
// Output: True

// Example 2:

// Input: "FlaG"
// Output: False

// Note: The input will be a non-empty word consisting of uppercase and
// lowercase latin letters.

#include <gtest/gtest.h>

#include <cctype>
#include <string>

class Solution {
  public:
  bool expectNoneOf(std::string::const_iterator begin,
                    std::string::const_iterator end, int test(int)) {
    for (auto it = begin; it != end; ++it) {
      if (test(*it)) {
        return false;
      }
    }
    return true;
  }

  bool detectCapitalUse(std::string word) {
    auto it = word.begin();
    if (std::isupper(*it)) {
      it++;
      if (it == word.end()) {
        return true;
      }
      if (std::isupper(*it)) {
        return expectNoneOf(it, word.end(), &std::islower);
      }
      return expectNoneOf(it, word.end(), &std::isupper);
    } else {
      return expectNoneOf(it, word.end(), &std::isupper);
    }
  }
};

TEST(T, T) {
  Solution s;
  ASSERT_EQ(s.detectCapitalUse("USA"), true);
  ASSERT_EQ(s.detectCapitalUse("leetcode"), true);
  ASSERT_EQ(s.detectCapitalUse("Google"), true);
  ASSERT_EQ(s.detectCapitalUse("FlaG"), false);
}
