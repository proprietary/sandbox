/*
 * Leetcode 48. Rotate Image
 * You are given an n x n 2D matrix representing an image.
 * 
 * Rotate the image by 90 degrees (clockwise).
 * 
 * Note:
 * 
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
 * 
 * Example 1:
 * 
 * Given input matrix = 
 * [
 *   [1,2,3],
 *   [4,5,6],
 *   [7,8,9]
 * ],
 * 
 * rotate the input matrix in-place such that it becomes:
 * [
 *   [7,4,1],
 *   [8,5,2],
 *   [9,6,3]
 * ]
 * Example 2:
 * 
 * Given input matrix =
 * [
 *   [ 5, 1, 9,11],
 *   [ 2, 4, 8,10],
 *   [13, 3, 6, 7],
 *   [15,14,12,16]
 * ], 
 * 
 * rotate the input matrix in-place such that it becomes:
 * [
 *   [15,13, 2, 5],
 *   [14, 3, 4, 1],
 *   [12, 6, 8, 9],
 *   [16, 7,10,11]
 * ]
 *
 */

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <ostream>
#include <tuple>
#include <utility>
#include <vector>

class Solution {
    public:
	int move_to(int N, int r, int c);

	std::pair<int, int> destination(int N, int r, int c) {
		int dest_c = N - r - 1;
		int dest_r = c;
		return {dest_r, dest_c};
	}

	void rotate_in_place(std::vector<std::vector<int>>& matrix) {
		auto N = matrix.size();
		int operations = 0;
		int r = 0, c = 0;
		int t = matrix[r][c];
		int start_r = r, start_c = c;
		int ops = 0;
		do {
			while (c < N - r - 1) {
				do {
					std::tie(r, c) = destination(N, r, c);
					/*
					std::cout << "r_dest,c_dest == " <<
					r_dest << ',' << c_dest << std::endl;
					std::cout << "moving " << t << " to ("
					<< r_dest << ',' << c_dest << ')' <<
					std::endl;
					*/
					std::swap(matrix[r][c], t);
					++ops;
					if (ops >= N * N) {
						return;
					}
				} while (!(r == start_r && c == start_c));
				++c;
				start_c = c;
				t = matrix[r][c];
			}
			++r;
			if (r >= N) {
				return;
			}
			c = r;
			start_r = r;
			start_c = r;
			t = matrix[r][c];

		} while (c <= N / 2 && r <= N / 2);
	}

	void rotate_copy(std::vector<std::vector<int>>& matrix) {
		auto N = matrix.size();
		std::vector<std::vector<int>> copy = matrix;
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				copy[r][c] = matrix[N - 1 - c][r];
				// auto [ q, w ] = destination(N, r, c);
				// copy[r][c] = matrix[q][w];
			}
		}
		matrix = std::move(copy);
	}

	void rotate(std::vector<std::vector<int>>& matrix) {
		// rotate_copy(matrix);
		rotate_in_place(matrix);
	}
};

std::ostream& operator<<(std::ostream& out,
			 std::vector<std::vector<int>>& matrix) {
	for (auto row : matrix) {
		for (auto col : row) {
			out << col << "\t";
		}
		out << std::endl;
	}
	return out;
}

static Solution s{};

TEST(Leetcode, TestCopyWithGivenExamples) {
	Solution s{};
	std::vector<std::vector<int>> example_1 = {
	    {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	std::cout << example_1 << std::endl;
	std::vector<std::vector<int>> example_1_expected = {
	    {7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
	s.rotate_copy(example_1);
	ASSERT_THAT(example_1, ::testing::Eq(example_1_expected));
}

TEST(Leetcode, TestInPlaceWithGivenExamples) {
	Solution s{};
	std::vector<std::vector<int>> example_1 = {
	    {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	std::cout << example_1 << std::endl;
	std::vector<std::vector<int>> example_1_expected = {
	    {7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
	s.rotate_in_place(example_1);
	std::cout << example_1 << std::endl;
	EXPECT_THAT(example_1, ::testing::Eq(example_1_expected));

	std::vector<std::vector<int>> example_2 = {
	    {5, 1, 9, 11},
	    {2, 4, 8, 10},
	    {13, 3, 6, 7},
	    {15, 14, 12, 16},
	};
	std::vector<std::vector<int>> example_2_expected = {
	    {15, 13, 2, 5},
	    {14, 3, 4, 1},
	    {12, 6, 8, 9},
	    {16, 7, 10, 11},
	};
	s.rotate_in_place(example_2);
	std::cout << example_2 << std::endl;
	EXPECT_THAT(example_2, ::testing::Eq(example_2_expected));
}

TEST(Leetcode, TestCase5) {
	Solution s{};
	std::vector<std::vector<int>> input = {{1, 2, 3, 4, 5},
					       {6, 7, 8, 9, 10},
					       {11, 12, 13, 14, 15},
					       {16, 17, 18, 19, 20},
					       {21, 22, 23, 24, 25}};
	std::vector<std::vector<int>> expected = {{21, 16, 11, 6, 1},
						  {22, 17, 12, 7, 2},
						  {23, 18, 13, 8, 3},
						  {24, 19, 14, 9, 4},
						  {25, 20, 15, 10, 5}};
	std::cout << input << std::endl;
	s.rotate(input);
	std::cout << input << std::endl;
	std::cout << expected << std::endl;
	EXPECT_THAT(input, ::testing::Eq(expected));
}

TEST(Leetcode, TestCase6) {
	Solution s{};
	std::vector<std::vector<int>> input = {
	    {2, 29, 20, 26, 16, 28}, {12, 27, 9, 25, 13, 21},
	    {32, 33, 32, 2, 28, 14}, {13, 14, 32, 27, 22, 26},
	    {33, 1, 20, 7, 21, 7},   {4, 24, 1, 6, 32, 34}};
	std::vector<std::vector<int>> expected = {
	    {4, 33, 13, 32, 12, 2},   {24, 1, 14, 33, 27, 29},
	    {1, 20, 32, 32, 9, 20},   {6, 7, 27, 2, 25, 26},
	    {32, 21, 22, 28, 13, 16}, {34, 7, 26, 14, 21, 28}};
	std::cout << input << std::endl;
	s.rotate(input);
	std::cout << input << std::endl;
	std::cout << expected << std::endl;
	EXPECT_THAT(input, ::testing::Eq(expected));
}

TEST(Leetcode, TestCase2) {
	std::vector<std::vector<int>> input = {{1}};
	std::vector<std::vector<int>> expected = {{1}};
	s.rotate(input);
	EXPECT_THAT(input, ::testing::Eq(expected));
}
