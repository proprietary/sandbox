#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  public:
  std::vector<std::string> fullJustify(std::vector<std::string>& words,
                                       int maxWidth) {
    std::vector<std::string> lines;
    lines.push_back("");
    for (const auto& word : words) {
      if (lines.back().length() == 0 ||
          lines.back().size() + word.length() + 1 <= maxWidth) {
        if (lines.back().length() > 0) lines.back().push_back(' ');
        std::copy(word.begin(), word.end(), std::back_inserter(lines.back()));
      } else {
        lines.push_back(word);
      }
    }
    for (auto line = lines.begin(); line != lines.end() - 1; line++) {
      if (line->length() >= maxWidth) {
        continue;
      }
      size_t next_space = 0;
      while (line->length() < maxWidth) {
        next_space = line->find(' ', next_space);
        if (next_space == std::string::npos) {
          next_space = line->find(' ', 0);
          if (next_space == std::string::npos) {
            line->insert(line->length(), maxWidth - line->length(), ' ');
            break;
          }
        }
        line->insert(next_space, 1, ' ');
        next_space = line->find_first_not_of(' ', next_space);
      }
    }
    lines.back().insert(lines.back().length(), maxWidth - lines.back().length(),
                        ' ');
    return lines;
  }
};

struct TestVec {
  std::vector<std::string> words;
  int max_width;
  std::vector<std::string> expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, minSteps) {
  auto tv = GetParam();

  const auto actual = Solution().fullJustify(tv.words, tv.max_width);

  EXPECT_EQ(actual, tv.expected);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
["This", "is", "an", "example", "of", "text", "justification."]
16
["This    is    an", "example  of text", "justification.  "]
["What","must","be","acknowledgment","shall","be"]
16
["What   must   be", "acknowledgment  ", "shall be        "]
["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]
20
["Science  is  what we", "understand      well", "enough to explain to", "a  computer.  Art is", "everything  else  we", "do                  "]
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 3);
  for (auto c : cases) {
    tvs.push_back(TestVec{.words = StringVecParser(c[0]).parse(),
                          .max_width = std::stoi(c[1]),
                          .expected = StringVecParser(c[2]).parse()});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
