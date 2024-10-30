#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class TrieNode {
  public:
  std::unordered_map<std::string_view, std::unique_ptr<TrieNode>> children;
  bool is_leaf = false;
  int count = 0;
};

class Trie {
  public:
  std::unique_ptr<TrieNode> root;

  Trie() : root{std::make_unique<TrieNode>()} {}

  void insert(const std::vector<std::string_view>& src) {
    TrieNode* cur = root.get();
    for (const auto c : src) {
      std::string_view folder{c.begin(), c.end()};
      if (!cur->children.contains(folder)) {
        cur->children[folder] = std::make_unique<TrieNode>();
      }
      cur = cur->children[folder].get();
      cur->count++;
    }
    cur->is_leaf = true;
  }
};

class Solution {
  std::vector<std::string_view> buf;

  std::vector<std::string_view>& split_string(std::string_view src) {
    buf.clear();
    size_t start = 0;
    size_t end = src.find('/');
    while (end != std::string_view::npos) {
      auto part = src.substr(start, end - start);
      if (!part.empty()) buf.push_back(part);
      start = end + 1;
      end = src.find('/', start);
    }
    buf.push_back(src.substr(start));
    return buf;
  }

  void dfs(std::vector<std::string>& out, TrieNode* node,
           std::string acc = "") {
    if (node->is_leaf) {
      out.push_back(acc);
    } else {
      for (const auto& [folder, child] : node->children) {
        dfs(out, child.get(), acc + "/" + std::string{folder});
      }
    }
  }

  public:
  std::vector<std::string> removeSubfoldersTrie(
      std::vector<std::string>& folders) {
    Trie t{};
    for (const auto& path : folders) {
      t.insert(split_string(path));
    }
    std::vector<std::string> res;
    res.reserve(folders.size());
    dfs(res, t.root.get());
    return res;
  }

  std::vector<std::string> removeSubfolders(std::vector<std::string>& folders) {
    std::vector<std::string> res;
    res.reserve(folders.size());
    std::sort(folders.begin(), folders.end(),
              [](const auto& a, const auto& b) { return a.size() < b.size(); });
    std::unordered_set<std::string_view> prefixes{};
    for (const auto& p : folders) {
      std::string_view folder = p;
      for (int j = folder.length() - 1; j > 0; j--) {
        while (folder[j] != '/') j--;
        if (j > 0) folder = folder.substr(0, j);
        if (prefixes.contains(folder)) {
          goto skip;
        }
      }
      res.push_back(p);
      prefixes.insert(p);
    skip:
    }
    return res;
  }
};

struct TestVec {
  std::vector<std::string> input;
  std::vector<std::string> expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  std::sort(tv.expected.begin(), tv.expected.end());
  auto result = Solution().removeSubfolders(tv.input);
  std::sort(result.begin(), result.end());
  EXPECT_EQ(tv.expected, result);
}

TEST_P(ParamTest, TrieSolution) {
  auto tv = GetParam();

  std::sort(tv.expected.begin(), tv.expected.end());
  auto result = Solution().removeSubfoldersTrie(tv.input);
  std::sort(result.begin(), result.end());
  EXPECT_EQ(tv.expected, result);
}

static auto cases = {
    TestVec{.input = {"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"},
            .expected = {"/a", "/c/d", "/c/f"}},
    TestVec{.input = {"/a", "/a/b/c", "/a/b/d"}, .expected = {"/a"}},
    TestVec{.input = {"/a/b/c", "/a/b/ca", "/a/b/d"},
            .expected = {"/a/b/c", "/a/b/ca", "/a/b/d"}}};
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
