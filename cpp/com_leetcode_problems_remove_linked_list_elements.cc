struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
  public:
  ListNode* removeElements(ListNode* head, int val) {
    auto new_head = head;
    auto node = head;
    ListNode* prev = nullptr;
    while (node != nullptr) {
      if (node->val == val) {
        if (prev == nullptr) {
          new_head = node->next;
        } else {
          prev->next = node->next;
        }
      } else {
        prev = node;
      }
      node = node->next;
    }
    return new_head;
  }
};
