#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>

void merge(std::vector<int>& a, std::vector<int>& b) {
	a.reserve(a.size() + b.size());
	a.insert(a.end(), b.begin(), b.end());
	std::sort(a.begin(), a.end());
	a.erase(std::unique(a.begin(), a.end()), a.end());
}

auto print_container(std::vector<int>& a) -> std::string {
	std::ostringstream ss;
	ss << "[ ";
	for (auto n : a) {
		ss << n << ", ";
	}
	ss << " ]" << std::endl;
	return ss.str();
}

struct Graph {
	std::vector<std::vector<int>> adj;
	auto size() -> size_t {
		return adj.size();
	}
	struct PathAnalysis {
		bool has_cycle;
		std::vector<int> vertices;
	};
	auto analyze_path_helper(std::vector<bool>& visited, int v) -> PathAnalysis {
		std::vector<int> vertices = {v};
		if (visited[v] == false) {
			visited[v] = true;
			for (auto w : adj[v]) {
				if (visited[w]) {
					return { .has_cycle = true, .vertices = vertices };
				}
				if (adj[w].size() > 0) {
					auto creates_cycle = analyze_path_helper(visited, w);
					merge(vertices, creates_cycle.vertices);
					if (creates_cycle.has_cycle) {
						return { .has_cycle = true, .vertices = vertices };
					}
				}
				vertices.push_back(w);
			}
		}
		return { .has_cycle = false, .vertices = vertices };
	}
	auto analyze_path(int v) -> PathAnalysis {
		std::vector<bool> visited(size(), false);
		return analyze_path_helper(visited, v);
	}
};


class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
		if (prerequisites.size() == 0) {
			return true;
		}
		Graph G;
        for (size_t i = 0; i < prerequisites.size(); ++i) {
			if (prerequisites[i].size() > 1) {
				auto v = prerequisites[i][0];
				auto w = prerequisites[i][1];
				if (G.adj.size() < std::max(v, w) + 1) {
					G.adj.resize(std::max(v, w) + 1);
				}
				// std::cout << "G size: " << G.adj.size() << std::endl;
				G.adj[v].push_back(w);
			}
		}
		std::vector<int> takeable_courses;
		bool any_cycle = false;
		for (size_t i = 0; i < G.size(); ++i) {
			std::cout << "G.adj[" << i << "]: " << print_container(G.adj[i]);
			auto a = G.analyze_path(i);
			if (a.has_cycle) {
				any_cycle = true;
				std::cout << "detected cycle at " << i << std::endl;
			}
			merge(takeable_courses, a.vertices);
		}
		std::cout << takeable_courses.size() << std::endl;
		std::cout << "takeable_courses: " << print_container(takeable_courses);
		std::cout << "any_cycle: " << any_cycle << std::endl;
		// std::cout << "adj: " << print_container(G.adj);
		return (G.size() < numCourses) || takeable_courses.size() >= numCourses;
    }
};

#include <gtest/gtest.h>

TEST(Test, Test1) {
	Solution s;
	std::vector<std::vector<int>> a = {{1,0}};
	ASSERT_EQ(true, s.canFinish(2, a));
}

TEST(Test, Test2) {
	Solution s;
	std::vector<std::vector<int>> a = {{1,0}, {0,1}};
	ASSERT_EQ(false, s.canFinish(2, a));
}

TEST(Test, Test3) {
	Solution s;
	std::vector<std::vector<int>> a = {{2,0},{1,0},{3,1},{3,2},{1,3}};
	ASSERT_EQ(false, s.canFinish(4, a));
}

TEST(Test, Test4) {
	Solution s;
	std::vector<std::vector<int>> a = {{0,1}};
	ASSERT_EQ(true, s.canFinish(2, a));
}

TEST(Test, Test5) {
	Solution s;
	std::vector<std::vector<int>> a = {{1,0}};
	ASSERT_EQ(true, s.canFinish(3, a));
}

TEST(Test, Test6) {
	Solution s;
	std::vector<std::vector<int>> a = {{0,1},{0,2},{1,2}};
	ASSERT_EQ(true, s.canFinish(3, a));
}

TEST(Test, Test10) {
	Solution s;
	std::vector<std::vector<int>> a = {{1,0},{2,6},{1,7},{6,4},{7,0},{0,5}};
	ASSERT_EQ(true, s.canFinish(8, a));
}
