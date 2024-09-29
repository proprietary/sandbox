#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <set>
#include <string>
#include <vector>

class MyCalendarTwo {
  struct Booking {
    int start;
    int end;
  };
  struct BookingCmp {
    bool operator()(const Booking& lhs, const Booking& rhs) const {
      return lhs.start != rhs.start ? lhs.start < rhs.start : lhs.end < rhs.end;
    }
  };
  std::set<Booking, BookingCmp> bookings_;
  std::set<Booking, BookingCmp> overlaps_;

  public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    Booking booking{.start = start, .end = end};
    if (auto other = overlaps_.lower_bound(booking);
        (other != overlaps_.end() && other->start < end) ||
        (other != overlaps_.begin() && (--other)->end > start)) {
      return false;
    }
    const auto lb = bookings_.lower_bound(booking);
    if (auto it = lb; it != bookings_.begin()) {
      do {
        it--;
      } while (it != bookings_.begin() && it->end <= start);
      if (it->end > start) {
        overlaps_.emplace(
            Booking{.start = start, .end = std::min(end, it->end)});
      }
    }
    for (auto it = lb; it != bookings_.end() && it->start < end; it++) {
      overlaps_.emplace(
          Booking{.start = it->start, .end = std::min(end, it->end)});
    }
    bookings_.insert(booking);
    return true;
  }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */

struct TestVec {
  std::vector<std::string> operations;
  std::vector<std::vector<int>> bookings;
  std::vector<bool> expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  MyCalendarTwo calendar{};

  ASSERT_EQ(tv.operations.size(), tv.bookings.size());
  std::vector<bool> actual;
  for (size_t i = 0; i < tv.operations.size(); i++) {
    if (tv.operations[i] == "book") {
      actual.push_back(calendar.book(tv.bookings[i][0], tv.bookings[i][1]));
    } else {
      calendar = MyCalendarTwo{};
    }
  }
  EXPECT_EQ(actual, tv.expected);
}

static const auto TEST_CASES = ::testing::Values(
    TestVec{.operations = {"MyCalendarTwo", "book", "book", "book", "book",
                           "book", "book"},
            .bookings =
                {{}, {10, 20}, {50, 60}, {10, 40}, {5, 15}, {5, 10}, {25, 55}},
            .expected = {true, true, true, false, true, true}},
    TestVec{.operations = {"MyCalendarTwo", "book", "book", "book", "book",
                           "book", "book", "book", "book", "book", "book"},
            .bookings = {{},
                         {24, 40},
                         {43, 50},
                         {27, 43},
                         {5, 21},
                         {30, 40},
                         {14, 29},
                         {3, 19},
                         {3, 14},
                         {25, 39},
                         {6, 19}},
            .expected = {true, true, true, true, false, false, true, false,
                         false, false}},
    TestVec{
        .operations = {"MyCalendarTwo", "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book"},
        .bookings = {{},       {47, 50}, {1, 10},  {27, 36}, {40, 47}, {20, 27},
                     {15, 23}, {10, 18}, {27, 36}, {17, 25}, {8, 17},  {24, 33},
                     {23, 28}, {21, 27}, {47, 50}, {14, 21}, {26, 32}, {16, 21},
                     {2, 7},   {24, 33}, {6, 13},  {44, 50}, {33, 39}, {30, 36},
                     {6, 15},  {21, 27}, {49, 50}, {38, 45}, {4, 12},  {46, 50},
                     {13, 21}},
        .expected = {true,  true,  true,  true,  true,  true,  true,  true,
                     false, false, false, false, false, true,  false, false,
                     false, true,  false, false, false, false, false, false,
                     false, false, true,  false, false, false}},
    TestVec{
        .operations = {"MyCalendarTwo", "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book", "book",
                       "book",          "book", "book", "book", "book"},
        .bookings = {{},        {33, 44}, {85, 95}, {20, 37},  {91, 100},
                     {89, 100}, {77, 87}, {80, 95}, {42, 61},  {40, 50},
                     {85, 99},  {74, 91}, {70, 82}, {5, 17},   {77, 89},
                     {16, 26},  {21, 31}, {30, 43}, {96, 100}, {27, 39},
                     {44, 55},  {15, 34}, {85, 99}, {74, 93},  {84, 94},
                     {82, 94},  {46, 65}, {31, 49}, {58, 73},  {86, 99},
                     {73, 84},  {68, 80}, {5, 18},  {75, 87},  {88, 100},
                     {25, 41},  {66, 79}, {28, 41}, {60, 70},  {62, 73},
                     {16, 33}},
        .expected = {true,  true,  true,  true,  false, true,  false, true,
                     false, false, false, true,  true,  false, true,  false,
                     false, true,  false, true,  false, false, false, false,
                     false, false, false, true,  false, false, false, false,
                     false, false, false, false, false, false, false, false}});

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
