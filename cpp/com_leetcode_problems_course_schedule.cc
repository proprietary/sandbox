#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <unordered_set>
#include <deque>
#include <stack>

void merge(std::vector<int>& a, std::vector<int>& b) {
	a.reserve(a.size() + b.size());
	a.insert(a.end(), b.begin(), b.end());
	std::sort(a.begin(), a.end());
	a.erase(std::unique(a.begin(), a.end()), a.end());
}

template<typename ContainerT>
auto print_container(ContainerT& a) -> std::string {
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
		std::vector<std::vector<int>> adj;
		adj.resize(numCourses);
		// Build adjacency list
		for (size_t i = 0; i < prerequisites.size(); ++i) {
			assert(prerequisites[i].size() == 2);
			auto v = prerequisites[i][0];
			auto w = prerequisites[i][1];
			auto required_size = std::max(v, w) + 1;
			if (adj.size() < required_size) {
				adj.resize(required_size);
			}
			adj[v].push_back(w);
		}
		// std::cout << "adjacency list:\n";
		// for (int i = 0; i < adj.size(); ++i) {
		// 	std::cout << "\tadj[" << i << "]: " << print_container(adj[i]);
		// }
		std::unordered_set<int> takeable_courses;
		for (int course_number = 0; course_number < numCourses; ++course_number) {
			if (adj[course_number].size() == 0) {
				// std::cout << "no prerequisites for course " << course_number << std::endl;
				takeable_courses.insert(course_number);
			} else if (takeable_courses.find(course_number) == takeable_courses.end()) {
				std::stack<int> frontier;
				std::for_each(adj[course_number].begin(), adj[course_number].end(), [&frontier](auto v) {
					frontier.push(v);
				});
				bool cyclic = false;
				std::vector<bool> on_stack(adj.size(), false);
				std::vector<bool> visited(adj.size(), false);
				visited[course_number] = true;
				on_stack[course_number] = true;
				while (!frontier.empty()) {
					int c = frontier.top();
					if (!visited[c]) {
						visited[c] = true;
						on_stack[c] = true;
					} else {
						on_stack[c] = false;
						frontier.pop();
					}
					for (auto const& v : adj[c]) {
						if (!visited[v]) {
							frontier.push(v);
						} else if (on_stack[v]) {
							cyclic = true;
							break;
						}
					}
				}
				if (!cyclic) {
					// std::cout << "no cycle found. adding..." << print_container(visited);
					for (size_t i = 0; i < visited.size(); ++i) {
						if (visited[i]) {
							takeable_courses.insert(i);
						}
					}
				} else {
					// std::cout << "cycle found " << print_container(visited);
				}
			}
		}
		// std::cout << "takeable_courses: " << print_container(takeable_courses);
		return takeable_courses.size() == numCourses;
    }
};

#include <gtest/gtest.h>

bool testCase(int n, std::vector<std::vector<int>> v) {
	return Solution().canFinish(n, v);
}

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

TEST(Test, Test11) {
	Solution s;
	std::vector<std::vector<int>> a = {{1,0},{0,2},{2,1}};
	ASSERT_EQ(false, s.canFinish(3, a));
}

TEST(Test, Test12) {
	Solution s;
	std::vector<std::vector<int>> a = {{0,2},{1,2},{2,0}};
	ASSERT_EQ(false, s.canFinish(3, a));
}

TEST(Test, Test13) {
	ASSERT_EQ(false, testCase(4, {{0,1},{3,1},{1,3},{3,2}}));
}
