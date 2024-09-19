#pragma once

#include <concepts>
#include <iostream>
#include <vector>

template <typename T>
concept PrintableArray = requires(T t) {
  { t.begin() } -> std::input_or_output_iterator;
  { t.end() } -> std::sentinel_for<decltype(t.begin())>;
  { std::cout << *t.begin() };
};

template <typename T>
concept PrintableMap = requires(T t) {
  { t.begin() } -> std::input_or_output_iterator;
  { t.end() } -> std::sentinel_for<decltype(t.begin())>;
  { std::cout << t.begin()->first };
  { std::cout << t.begin()->second };
};

template <typename T, size_t N>
constexpr size_t sizeof_array(T (&arr)[N]) {
  return N;
}

template <typename It>
void print_array(It begin, It end);

template <typename It>
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

template <PrintableMap T>
void print_map(const T& m) {
  print_array(m.begin(), m.end(), [](const auto x) { return "(" + std::to_string(x->first) + ", " + std::to_string(x->second) + ")"; });
}

template <PrintableArray T>
void print_array(const T& arr) {
  print_array(arr.begin(), arr.end(), [](const auto x) { return *x; });
}

template <typename It, typename F>
void print_array(It begin, It end, F accessor_fn) {
  std::cout << "[ ";
  for (auto it = begin; it != end; ++it) {
    std::cout << accessor_fn(it) << ", ";
  }
  std::cout << " ]\n";
}

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
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
