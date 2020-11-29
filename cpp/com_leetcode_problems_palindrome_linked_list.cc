#include <bits/stdc++.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	size_t length(ListNode* head) {
		size_t n = 0;
		while (head != nullptr) {
			n += 1;
			head = head->next;
		}
		return n;
	}

	ListNode* reverse(ListNode* begin, ListNode* end) {
		assert(begin != nullptr);
		ListNode* c = nullptr;
		while (begin != nullptr && begin != end) {
			auto* n = begin->next;
			begin->next = c;
			c = begin;
			begin = n;
		}
		return c;
	}

	bool equal(ListNode* begin1, ListNode* end1, ListNode* begin2, ListNode* end2) {
		while (begin1 != end1 && begin2 != end2) {
			if (begin1->val != begin2->val) {
				return false;
			}
			begin1 = begin1->next;
			begin2 = begin2->next;
		}
		return begin1 == end1 && begin2 == end2;
	}
	
	bool isPalindrome(ListNode* head) {
		if (head == nullptr) {
			return true;
		}
		auto len = length(head);
		if (len == 1) {
			return true;
		} else if (len == 2) {
			return head->val == head->next->val;
		} else if (len == 3) {
			return head->val == head->next->next->val;
		}
		auto mid = len / 2;
		ListNode* p = nullptr;
		size_t c = 0;
		while (head != nullptr && c++ < mid) {
			auto* n = head->next;
			head->next = p;
			p = head;
			head = n;
		}
		ListNode* left = p;
		ListNode* const left_end = len % 2 == 0 ? head : head->next;
		ListNode* right = left_end;
		for (auto* it = left; it != nullptr && it != right; it = it->next) {
			std::cout << it->val << ", ";
		}
		std::cout << std::endl;
		for (auto* it = right; it != nullptr; it = it->next) {
			std::cout << it->val << ", ";
		}
		std::cout << std::endl;
		for (auto i = 0UL; i < mid; ++i) {
			if (left->val != right->val) {
				return false;
			}
			left = left->next;
			right = right->next;
		}
		return true;
	}
};
