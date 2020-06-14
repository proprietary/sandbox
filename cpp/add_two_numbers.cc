/*
 * Leetcode 2. Add Two Numbers
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their nodes
 * contain a single digit. Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 *
 * Example:
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 *
 */

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
  bool operator==(const ListNode& other) {
    auto* it = this;
    auto* other_it = &other;
    for (; other_it != nullptr; it = it->next, other_it = other_it->next) {
      if (it == nullptr || it->val != other_it->val) {
        return false;
      }
    }
    return true;
  }
  ListNode(std::vector<int>&& x) {
    if (x.size() == 0) {
      throw new std::runtime_error{
          "attempt to construct a list with no elements"};
    }
    auto* cursor = this;
    auto it = x.begin();
    val = *it++;
    for (; it != x.end(); ++it) {
      cursor->next = new ListNode{*it};
      cursor = cursor->next;
    }
    cursor->next = nullptr;
  }
};

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr || l2 == nullptr) return nullptr;
    int carry = 0;
    ListNode *l1_iter = l1, *l2_iter = l2, *l1_prev = nullptr;
    while (l2_iter != nullptr || carry > 0) {
      if (l2_iter != nullptr) {
        carry += l2_iter->val;
        l2_iter = l2_iter->next;
      }
      if (l1_iter != nullptr) {
        carry += l1_iter->val;
        l1_iter->val = carry % 10;
      } else {
        l1_iter = new ListNode{carry % 10};
        l1_prev->next = l1_iter;
      }
      l1_prev = l1_iter;
      l1_iter = l1_iter->next;
      carry /= 10;
    }
    return l1;
  }
};

void print(ListNode* l) {
  for (; l != nullptr; l = l->next) {
    std::cout << l->val << ' ';
  }
  std::cout << std::endl;
}

TEST(Leetcode2, TestGivenExample) {
  ListNode a{{2, 4, 3}};
  ListNode b{{5, 6, 4}};
  ListNode expected{{7, 0, 8}};
  Solution s{};
  auto* res = s.addTwoNumbers(&a, &b);
  if (!(*res == expected)) {
    print(&expected);
    print(res);
  }
  EXPECT_TRUE(*res == expected);
}

TEST(Leetcode2, TestAnotherGivenExample) {
  ListNode a{5};
  ListNode b{5};
  ListNode expected{{0, 1}};
  Solution s{};
  auto* res = s.addTwoNumbers(&a, &b);
  if (!(*res == expected)) {
    print(&expected);
    print(res);
  }
  EXPECT_TRUE(*res == expected);
}

TEST(Leetcode2, TestAutomatedCases) {
  Solution s{};
  auto generate_list_node = [](int n) -> ListNode* {
    std::vector<int> nums{};
    while (n > 0) {
      nums.push_back(n % 10);
      n /= 10;
    }
    return new ListNode{std::move(nums)};
  };
  for (int i = 1; i < 1'000; ++i) {
    for (int j = 1; j < 1'000; ++j) {
      auto* expected = generate_list_node(i + j);
      auto* a = generate_list_node(i);
      auto* b = generate_list_node(j);
      auto* res = s.addTwoNumbers(a, b);
      if (!(*res == *expected)) {
        std::cout << "input: " << i << ", " << j << std::endl;
        std::cout << "expected: " << std::endl;
        print(expected);
        std::cout << "actual: \n";
        print(res);
      }
      ASSERT_TRUE(*res == *expected);
    }
  }
}
