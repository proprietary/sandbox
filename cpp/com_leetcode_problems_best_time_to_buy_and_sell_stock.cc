// tests:
// clang++ -std=c++17 -lgtest -lgtest_main -pthread com_leetcode_problems_best_time_to_buy_and_sell_stock.cc && ./a.out
// benchmarks:
// clang++ -std=c++17 -lbenchmark -lbenchmark_main -lgtest -pthread com_leetcode_problems_best_time_to_buy_and_sell_stock.cc && ./a.out
#include <benchmark/benchmark.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <random>
#include <vector>

class Solution {
    public:
	int maxProfit(std::vector<int>& prices) {
		int cheapest_so_far = std::numeric_limits<int>::max();
		int max_profit = 0;
		for (int price : prices) {
			const auto difference = price - cheapest_so_far;
			if (difference < 0) {
				cheapest_so_far = price;
			} else if (difference > max_profit) {
				max_profit = difference;
			}
		}
		return max_profit;
	}
};

int max_profit_quadratic(std::vector<int>& prices) {
	int max_profit = 0;
	for (auto it = prices.rbegin(); it != prices.rend(); ++it) {
		int cheapest_below = *std::min_element(it, prices.rend());
		auto profit = *it - cheapest_below;
		if (profit > max_profit) {
			max_profit = profit;
		}
	}
	return max_profit;
}

template <typename T>
std::vector<T> random_vec(size_t max_size, size_t min_size = 0,
			  int lower_bound = 0, int upper_bound = 1'000'000) {
	// generate random vector
	std::random_device rd{};
	std::mt19937 mt{rd()};
	std::uniform_int_distribution<T> values_dist{lower_bound, upper_bound};
	std::uniform_int_distribution<size_t> sz_dist{min_size, max_size};
	auto sz = sz_dist(mt);
	std::vector<T> out;
	out.reserve(sz);
	for (int i = 0; i < sz; ++i) {
		out.push_back(values_dist(mt));
	}
	return out;
}

TEST(QuadraticComplexity, TestGivenExamples) {
	{
		std::vector<int> input{{7, 1, 5, 3, 6, 4}};
		EXPECT_EQ(5, max_profit_quadratic(input));
	}
	{
		std::vector<int> input{{7, 6, 4, 3, 1}};
		EXPECT_EQ(0, max_profit_quadratic(input));
	}
}

TEST(Leetcode, TestGivenExamples) {
	Solution s{};
	{
		std::vector<int> input{{7, 1, 5, 3, 6, 4}};
		EXPECT_EQ(5, s.maxProfit(input));
	}
	{
		std::vector<int> input{{7, 6, 4, 3, 1}};
		EXPECT_EQ(0, s.maxProfit(input));
	}
}

TEST(Leetcode, TestAgainstQuadratic) {
	Solution s{};
	constexpr auto iters = 10'000;
	for (int i = 0; i < iters; ++i) {
		auto v = random_vec<int>(500);
		auto expected = max_profit_quadratic(v);
		auto actual = s.maxProfit(v);
		if (expected != actual) {
			fmt::print("vector: {}",
				   fmt::join(v.begin(), v.end(), ", "));
		}
		ASSERT_EQ(expected, actual);
	}
}

static void BM_Solution(benchmark::State& state) {
	Solution s{};
	auto input = random_vec<int>(1'000'000, 1'000'000);
	for (auto _ : state) {
		(void)s.maxProfit(input);
	}
}

static void BM_SolutionSmall(benchmark::State& state) {
	Solution s{};
	std::vector<int> input{{7, 1, 5, 3, 6, 4}};
	for (auto _ : state) {
		(void)s.maxProfit(input);
	}
}

BENCHMARK(BM_Solution);
BENCHMARK(BM_SolutionSmall);
