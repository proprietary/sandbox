#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <limits>
#include <map>
#include <string>
#include <string_view>
#include <vector>

class Solution {
  std::string_view formula_;
  size_t pos_ = 0;

  public:
  Solution() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }

  char peek() { return pos_ < formula_.length() ? formula_[pos_] : '\0'; }

  char consume() { return pos_ < formula_.length() ? formula_[pos_++] : '\0'; }

  int32_t parse_count() {
    if (!std::isdigit(peek())) return 1;
    int32_t count = 0;
    while (std::isdigit(peek())) {
      count = count * 10 + (consume() - '0');
    }
    return count;
  }

  std::string parse_atom() {
    std::string atom_name;
    atom_name += consume();
    while (std::islower(peek())) {
      atom_name += consume();
    }
    return atom_name;
  }

  std::map<std::string, int32_t> parse_group() {
    std::map<std::string, int32_t> res;
    while (peek() != ')' && peek() != '\0') {
      if (peek() == '(') {
        consume();
        auto subgroup = parse_group();
        consume();
        int32_t count = parse_count();
        for (const auto &[atom_name, atom_count] : subgroup) {
          res[atom_name] += atom_count * count;
        }
      } else if (std::isupper(peek())) {
        auto atom_name = parse_atom();
        auto count = parse_count();
        res[atom_name] += count;
      } else {
        std::cerr << "wat\n";
      }
    }
    return res;
  }

  std::string countOfAtoms(std::string formula) {
    formula_ = formula;
    pos_ = 0;
    const auto group = parse_group();
    std::string ans;
    for (const auto &[atom, count] : group) {
      ans += atom;
      if (count > 1) ans += std::to_string(count);
    }
    return ans;
  }
};

struct TestVec {
  std::string formula;
  std::string expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, CountAtoms) {
  const auto &tv = GetParam();

  const std::string actual = Solution().countOfAtoms(tv.formula);

  EXPECT_EQ(actual, tv.expected);
}

static const auto TEST_CASES =
    ::testing::Values(TestVec{"H2O", "H2O"}, TestVec{"Mg(OH)2", "H2MgO2"},
                      TestVec{"K4(ON(SO3)2)2", "K4N2O14S4"});

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
