#pragma once

#include <iostream>
#include <vector>

template<typename It>
void print_array(It begin, It end);

template<typename It>
void print_2d_array(It begin, It end) {
    std::cout << "[ ";
    for (auto it = begin; it != end; ++it) {
        print_array(it->begin(), it->end());
        if (it + 1 != end) {
            std::cout << ", ";
        }
    }
    std::cout << " ]\n";

}

template<typename It>
void print_array(It begin, It end) {
    std::cout << "[ ";
    for (auto it = begin; it != end; ++it) {
        std::cout << *it;
        if (it + 1 != end) {
            std::cout << ", ";
        }
    }
    std::cout << " ]\n";
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ~ListNode() {
        if (next != nullptr) {
            delete next;
        }
    }
};

ListNode* newList(std::vector<int> src) {
    ListNode* head = new ListNode();
    ListNode* p = head;
    for (int i = 0; i < src.size(); i++) {
        p->val = src[i];
        if (i + 1 < src.size()) {
            p->next = new ListNode();
            p = p->next;
        }
    }
    return head;
}
