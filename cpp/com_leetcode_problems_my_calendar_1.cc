#include <gtest/gtest.h>

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "utils.hpp"

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

class MyCalendar {
  std::map<int, int> bookings_;

  public:
  MyCalendar() {}

  bool book(int start, int end) {
    auto other = bookings_.upper_bound(start);
    if (other != bookings_.end() && other->second < end) {
      return false;
    }
    bookings_[end] = start;
    return true;
  }
};

struct TestVec {
  std::vector<std::string> operations;
  std::vector<std::vector<int>> bookings;
  std::vector<bool> expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  MyCalendar calendar{};

  ASSERT_EQ(tv.operations.size(), tv.bookings.size());
  print_array(tv.expected);
  for (size_t i = 0; i < tv.operations.size(); i++) {
    if (tv.operations[i] == "book") {
      ASSERT_EQ(calendar.book(tv.bookings[i][0], tv.bookings[i][1]),
                tv.expected[i]);
    } else {
      calendar = MyCalendar{};
    }
  }
}

auto parse_test_cases() {
  std::vector<TestVec> tvs;
  tvs.emplace_back(TestVec{.operations = {"MyCalendar", "book", "book", "book"},
                           .bookings = {{}, {10, 20}, {15, 25}, {20, 30}},
                           .expected = {true, true, false, true}});
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
