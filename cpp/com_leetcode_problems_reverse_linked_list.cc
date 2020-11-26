#include <bits/stdc++.h>
#include <initializer_list>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

auto make_list(std::vector<int> src) -> ListNode* {
	ListNode* head = nullptr;
	ListNode* prev = nullptr;
	ListNode* cur = nullptr;
	auto it = src.begin();
	if (src.size() > 1) {
		head = new ListNode(*it);
		prev = head;
		while (++it != src.end()) {
			cur = new ListNode;
			cur->val = *it;
			prev->next = cur;
			prev = cur;
		}
	}
	return head;
}

auto list_equal(ListNode* a, ListNode* b) -> bool {
	while (a != nullptr && b != nullptr) {
		if (a->val != b->val) {
			return false;
		}
		a = a->next;
		b = b->next;
	}
	return a == nullptr && b == nullptr;
}

auto print_list(std::ostream& output, ListNode* src) -> void {
	while (src != nullptr) {
		output << src->val << ", ";
		src = src->next;
	}
	output << std::endl;
}

class Solution {
public:
	// ListNode* reverseList(ListNode* head) {
	// 	ListNode* p = nullptr;
	// 	while (head != nullptr) {
	// 		auto* real_next = head->next;
	// 		head->next = p;
	// 		p = head;
	// 		head = real_next;
	// 	}
	// 	return p;
	// }

	ListNode* reverseList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		auto* p = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return p;
	}
};

#include <gtest/gtest.h>

TEST(Test, Test1) {
	auto* list_1 = make_list({1, 2, 3, 4, 5});
	auto* list_2 = make_list({5, 4, 3, 2, 1});
	auto* reversed_list_1 = Solution().reverseList(list_1);
	print_list(std::cout, reversed_list_1);
	ASSERT_TRUE(list_equal(reversed_list_1, list_2));
}
