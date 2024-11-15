#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
class Solution {
  public:
  int maximumSwap3(int num) {
    std::string n = std::to_string(num);
    const size_t N = n.size();
    if (N == 1) {
      return num;
    }
    size_t swap_1 = N - 1;
    size_t swap_2 = N - 1;
    size_t max_idx = N - 1;
    for (size_t i = N - 2; i < static_cast<size_t>(-1); --i) {
      if (n[i] > n[max_idx]) {
        max_idx = i;
      } else if (n[i] < n[max_idx]) {
        swap_1 = i;
        swap_2 = max_idx;
      }
    }
    std::swap(n[swap_1], n[swap_2]);
    return std::stoi(n);
  }

  int maximumSwap2(int num) {
    std::string n = std::to_string(num);
    const size_t N = n.size();

    if (N == 1) {
      return num;
    }

    // first pass to populate array with indices of max element to the right
    std::vector<int> max_rtl(N);
    max_rtl[N - 1] = N - 1;
    for (int idx = N - 2; idx >= 0; --idx) {
      max_rtl[idx] = (n[idx] > n[max_rtl[idx + 1]]) ? idx : max_rtl[idx + 1];
    }

    // second pass to greedily find the maximum swap
    for (int idx = 0; idx < N; ++idx) {
      if (n[idx] < n[max_rtl[idx]]) {
        std::swap(n[idx], n[max_rtl[idx]]);
        return std::stoi(n);
      }
    }

    // no maximum swap found
    return num;
  }

  int maximumSwap(int num) {
    std::string n = std::to_string(num);
    int best = num;
    for (auto it = n.begin(); it != n.end(); ++it) {
      for (auto jt = it + 1; jt != n.end(); ++jt) {
        std::iter_swap(it, jt);
        const int swapped = std::stoi(n);
        best = std::max(best, swapped);
        std::iter_swap(it, jt);
      }
    }
    return best;
  }
};

struct TV {
  int num;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().maximumSwap(tv.num);
  EXPECT_EQ(tv.expected, actual);
}

TEST_P(ParamTest, Solution2) {
  auto tv = GetParam();

  auto actual = Solution().maximumSwap2(tv.num);
  EXPECT_EQ(tv.expected, actual);
}

TEST_P(ParamTest, Solution3) {
  auto tv = GetParam();

  auto actual = Solution().maximumSwap3(tv.num);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{2736, 7236},
    TV{9973, 9973},
    TV{1, 1},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

static void run_solution1(::benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(Solution().maximumSwap(state.range(0)));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(run_solution1)->Range(1, 100000000)->Complexity();

static void run_solution2(::benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(Solution().maximumSwap2(state.range(0)));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(run_solution2)->Range(1, 100000000)->Complexity();

static void run_solution3(::benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(Solution().maximumSwap3(state.range(0)));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(run_solution3)->Range(1, 100000000)->Complexity();

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  ::benchmark::Initialize(&argc, argv);

  // ::benchmark::RunSpecifiedBenchmarks();

  return RUN_ALL_TESTS();
}
