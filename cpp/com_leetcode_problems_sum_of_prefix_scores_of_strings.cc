#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "test_case_helper.hpp"

template <typename T, std::size_t N>
constexpr std::array<T, N> make_array(T&& value) {
  std::array<T, N> arr{};
  for (std::size_t i = 0; i < N; ++i) {
    arr[i] = value;
  }
  return arr;
}

template <size_t CHARSET_LEN = 26, int EMPTY = -1>
struct TrieNode {
  std::array<int32_t, CHARSET_LEN> children;
  int count;
  bool is_end_of_word;

  TrieNode()
      : children(make_array<int32_t, CHARSET_LEN>(EMPTY)),
        count{0},
        is_end_of_word{false} {}

  int32_t& operator[](std::size_t idx) { return children[idx]; }

  int32_t operator[](std::size_t idx) const { return children[idx]; }
};

template <size_t CHARSET_LEN = 26, int EMPTY = -1>
class Trie {
  std::vector<TrieNode<CHARSET_LEN, EMPTY>> nodes_;

  static inline int char_to_index(char c) noexcept { return c - 'a'; }

  public:
  Trie(std::size_t max_size) {
    nodes_.reserve(max_size);
    nodes_.emplace_back();
  }

  template <typename It>
  void insert(It begin, It end) {
    std::for_each(begin, end, [this](const auto& c) { this->insert(c); });
  }

  void insert(std::string_view str) {
    int64_t cur = 0;
    for (const auto c : str) {
      const auto idx = char_to_index(c);
      if (nodes_[cur][idx] == EMPTY) {
        nodes_[cur][idx] = nodes_.size();
        nodes_.emplace_back(TrieNode{});
      }
      cur = nodes_[cur][idx];
      nodes_[cur].count++;
    }
    nodes_[cur].is_end_of_word = true;
  }

  bool starts_with(std::string_view prefix) const {
    int64_t cur = 0;
    for (const auto c : prefix) {
      const auto idx = char_to_index(c);
      if (nodes_[cur][idx] == EMPTY) {
        return false;
      }
      cur = nodes_[cur][idx];
    }
    return true;
  }

  int count(std::string_view word) const {
    int count = 0;
    int64_t cur = 0;
    for (const auto c : word) {
      const auto idx = char_to_index(c);
      if (nodes_[cur][idx] == EMPTY) {
        return count;
      }
      cur = nodes_[cur][idx];
      count += nodes_[cur].count;
    }
    return count;
  }

  bool contains(std::string_view str) const {
    int64_t cur = 0;
    for (const auto c : str) {
      const auto idx = char_to_index(c);
      if (nodes_[cur][idx] == EMPTY) {
        return false;
      }
      cur = nodes_[cur][idx];
    }
    return nodes_[cur].is_end_of_word;
  }
};

class Solution {
  public:
  std::vector<int> sumPrefixScores(std::vector<std::string>& words) {
    std::vector<int> ans(words.size(), 0);
    Trie<26> trie(1000);
    trie.insert(words.begin(), words.end());
    for (size_t i = 0; i < words.size(); ++i) {
      ans[i] = trie.count(words[i]);
    }
    return ans;
  }
};

struct TestVec {
  std::vector<std::string> input;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  EXPECT_EQ(Solution().sumPrefixScores(tv.input), tv.expected);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
["abc","ab","bc","b"]
[5,4,3,2]
["abcd"]
[4]
["togpxeegtdcnhhinvzebdkedcgdnqklb","xtvppwnocdqhkpputujvlmvpkjbprrfhusdspkrsicsdpxtnmpwxuyufrelffpkwzoajjukpj","xpztiaclccxksrsgxgbreyhsfbloqecuroxvhpbcgbhyfvkoczyhfqfrdjskvyqjvatznihaakhxzkibghtlczkxiaxsyqwgerr","hpqeovidwtkzfjeocvttzfpabumpgawpoqmqraehjiasjsunzryjnbugiolqbvuimhhkrryzqmkfsnkss","fypqcvnhvfdjukdyvtmottdqtraztqjsehmzisldmwutraciiuptnrogwdbqsficpjfotwyvlgmubjdtcpempuydkboebere","xtvppwnocdqhkpputujvlmvpkjbprrfhusdspkrsicsdpxtnmpwxuyuaplytkpdefg","xtvppwnocdqhkpputujvlmvpkjbprrfhusdspkrsicsdpxtnmpwxuyufrlcdesbixceczxwcgofehkwuhhyuoxfmsjzonclbk","fypqcvnhvfdjukdyvtmottdqtraztqjsehmzisldmwutraciiuptnrogwdbqsficpjfotwyvlgmubjdtcpehsdnadbtqapaq","dikqtanjtzbafrvebgvsvmiieqztkreifirlgzbetycusmjzbidqgkdpbnmrscswxbkckkgnpprwoybpentdgnwoklwunovdyv","ggyruovnolipmgchrfqgfsgxnxptvddpynyapwjthyaoiuqmawfhwnhyjvgktrzwywpoukzjsvqtfivbqybhhzbnnlejgzoqqnih","xpztiaclccxksrsgxgbreyhsfbloqecuroxvhpbcgbhyfvkoczyhfqfrdjcffkiumslpccvvpjxoqvgganxaculkqqqvgbmecnmd","ggyruovnolipmgchrfqgfsgxnxptvddpynyapwjthyaoiuqmawfhwnhyjvgktrzwywpoukzjsvqtfivbqybhhzbnnlejgzoqqnt","fypqcvnhvfoqyivgjrohgyoycyaryuwzhabluicrgtr","ggyruovnolipmgchrfqgfsgxnxptvddpynyapwjthyaoiuqmawfhwnhyjvgktrzwywpoukzjsvqtfivbqybhhzbnqmmzozlqg","hpqeovidwtkzfjeocvttzfpabumpgawpoqmqraeadrugudcypawdqoczlmkeedjjmzvozdvrztjanhhmwhzivblbpgexrdtrerto","dikqtanjtzbafrvebgvsvmiieqztkreifirlgrofgxkxfgsilxfhqoaqzlfetnafsokjaevfqaymdqxyapmyfxh","dikqtanjtzbafrvebgvsvmiieqztkreifirlgzbetycusmjzbidqgkdpbnmrscswxbkckkgnpprwoybpentdgnwoklwunovdwwfc","xtvppwnocdqhkpputujvlmvpkjbprrfhusdspkrsicsdpxtnmpwxuyufrlcdesbixceczxwcgofehkwuhhyuoxfmsjzonczwcb","hpqeovidwtkzfjeocvttzfpabumpgawpoqmqraeadrugudcypawduddlnxfsvwkkgmnszndsxndepsoenpghv","fypqcvnhvfdjukdyvtmottdqtraztqjsehmzisldmwutraciiuptnrogwdbqsficpjfotwyvlgmubjdtcpempuydkboeofavkgaa","xtvppwnocdqhkpputujvlmvpkjbprrfhusdewtyktcieushmffhqxhojdfylrvodheajbemvuclyiugrdeikuycmpoe","fypqcvnhvfdjukdyvtmottdqtraztqjsehmzisldmwutraciiuptnrogwdbqsficpjfotwyvlgmubjdtcpempuydkboeoeszf","dikqtanjtzbafrvebgvsvmiieqztkreifirlgzbetycusmjzbidqgkdpbnmrscswxbkckkgnpprwoybpentdgnwoklwunovdwwa","fypqcvnhvfdjukdyvtmottdqtraztqjsehmzisldmwutraciiuptnrogwdbqsficpjfotwyvlgmubjdtcpempuydkboeoernkyia","dikqtanjtzbafrvebgvsvmiieqztkreifirlgzbetycusmjzbidqgkdpbnmrscswxbkckkgnpprwoybpentdgnwoklwunovdwb","fypqcvnhvfdgaxmxnqrwvdkpazzj","xtvppwnocdqhkpputujvlmvpkjbprrfhusdspkrsicsdpxtnmpwxuyufrlcdesbixceczxwcgofehkwuhhyuoxfmsjzonclbyox","togpxeegtdcnhhinvzebdkplochcjqockwcngdobprvkvrukyqcynzpigfqnhgseroesxqdgjdbmfmicn"]
[54,336,163,159,476,323,436,449,423,286,164,285,103,273,191,235,428,435,176,482,268,480,427,483,425,93,438,103]
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 2);
  for (auto c : cases) {
    tvs.push_back(TestVec{.input = StringVecParser(c[0]).parse(),
                          .expected = IntVecParser(c[1]).parse()});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
