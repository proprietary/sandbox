#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

struct ChairAssignment {
  int leaving;
  int seat_number;
};

struct ChairAssignmentComparator {
  bool operator()(const ChairAssignment& a, const ChairAssignment& b) {
    return a.leaving > b.leaving;
  }
};

class Solution {
  public:
  int smallestChair(std::vector<std::vector<int>>& times, int target_friend) {
    std::priority_queue<ChairAssignment, std::vector<ChairAssignment>,
                        ChairAssignmentComparator>
        q;
    std::vector<int> unoccupied_chairs;
    const auto target_arrival_time = times[target_friend][0];

    std::sort(times.begin(), times.end());
    int starting_chair = 0;
    for (const auto& t : times) {
      // New person came in
      const auto arrival = t[0];
      const auto leaving = t[1];

      // Mark the chairs people have left as unoccupied
      while (!q.empty() && arrival >= q.top().leaving) {
        unoccupied_chairs.push_back(q.top().seat_number);
        std::push_heap(unoccupied_chairs.begin(), unoccupied_chairs.end(),
                       std::greater{});
        q.pop();
      }

      // Assign chair number
      int seat_number;
      if (!unoccupied_chairs.empty()) {
        // Choose the smallest unoccupied chair
        std::pop_heap(unoccupied_chairs.begin(), unoccupied_chairs.end(),
                      std::greater{});
        seat_number = unoccupied_chairs.back();
        unoccupied_chairs.pop_back();
      } else {
        seat_number = starting_chair++;
      }
      q.push({leaving, seat_number});

      // Check if this is our friend
      if (target_arrival_time == arrival) {
        return seat_number;
      }
    }
    return 0;
  }
};

struct TestVec {
  std::vector<std::vector<int>> times;
  int target_friend;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected, Solution().smallestChair(tv.times, tv.target_friend));
}

static auto cases = {
    TestVec{
        .times = {{1, 4}, {2, 3}, {4, 6}}, .target_friend = 1, .expected = 1},
    TestVec{
        .times = {{3, 10}, {1, 5}, {2, 6}}, .target_friend = 0, .expected = 2},
    TestVec{.times = {{33889, 98676},
                      {80071, 89737},
                      {44118, 52565},
                      {52992, 84310},
                      {78492, 88209},
                      {21695, 67063},
                      {84622, 95452},
                      {98048, 98856},
                      {98411, 99433},
                      {55333, 56548},
                      {65375, 88566},
                      {55011, 62821},
                      {48548, 48656},
                      {87396, 94825},
                      {55273, 81868},
                      {75629, 91467}},
            .target_friend = 6,
            .expected = 2}};
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
