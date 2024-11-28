#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <unordered_map>
#include <vector>

namespace {
template <typename T, std::size_t N>
struct array_hash {
  std::size_t operator()(const std::array<T, N>& a) const {
    const size_t p = 31;
    const size_t m = 1e9 + 9;
    size_t hash_value = 0;
    size_t p_pow = 1;

    for (int num : a) {
      hash_value = (hash_value + (num + 1) * p_pow) % m;
      p_pow = (p_pow * p) % m;
    }
    return hash_value;
  }
};

class Solution {
  static constexpr int kRows = 2;
  static constexpr int kCols = 3;
  using Board = std::array<int, kRows * kCols>;
  std::vector<std::vector<int>> possible_moves = {
      {1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {4, 2},
  };
  static constexpr Board finished{1, 2, 3, 4, 5, 0};

  void dfs(
      std::unordered_map<Board, int, array_hash<int, kRows * kCols>>& visited,
      Board& board, int idx, int count = 0) {
    if (visited.contains(board) && visited[board] <= count) {
      return;
    }
    visited[board] = count;
    for (const int next_move : possible_moves[idx]) {
      std::swap(board[idx], board[next_move]);
      dfs(visited, board, next_move, count + 1);
      std::swap(board[idx], board[next_move]);
    }
  }

  public:
  int slidingPuzzle(std::vector<std::vector<int>>& board) {
    std::unordered_map<std::array<int, kRows * kCols>, int,
                       array_hash<int, kRows * kCols>>
        visited;
    Board b;
    for (int i = 0, k = 0; i < kRows; ++i) {
      for (int j = 0; j < kCols; ++j) {
        b[k++] = board[i][j];
      }
    }
    const int zero_idx = std::ranges::find(b, 0) - b.begin();
    dfs(visited, b, zero_idx);
    if (visited.contains(finished)) {
      return visited[finished];
    } else {
      return -1;
    }
  }
};

struct TV {
  std::vector<std::vector<int>> board;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().slidingPuzzle(tv.board);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{{1, 2, 3}, {4, 0, 5}}, 1},
    TV{{{1, 2, 3}, {5, 4, 0}}, -1},
    TV{{{4, 1, 2}, {5, 0, 3}}, 5},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
