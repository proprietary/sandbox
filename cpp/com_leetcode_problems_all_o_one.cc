#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <list>
#include <map>
#include <string>

// namespace {
// void print(const std::map<int, std::list<std::string>>& src) {
//   std::cout << "[";
//   for (const auto& [count, lst] : src) {
//     std::cout << "{" << count << ": [";
//     for (const auto& s : lst) {
//       std::cout << s << ", ";
//     }
//     std::cout << "], ";
//   }
//   std::cout << "]\n";
// }
// }  // namespace

class AllOne {
  std::unordered_map<std::string, int> counts_;
  std::map<int, std::list<std::string>> keys_;

  public:
  AllOne() {}

  void inc(std::string key) {
    const int old_count = counts_[key]++;
    if (keys_.contains(old_count)) {
      if (auto to_remove =
              std::find(keys_[old_count].begin(), keys_[old_count].end(), key);
          to_remove != keys_[old_count].end()) {
        keys_[old_count].erase(to_remove);
      }
      if (keys_[old_count].empty()) {
        keys_.erase(old_count);
      }
    }
    keys_[counts_[key]].push_front(key);
  }

  void dec(std::string key) {
    const int old_count = counts_[key]--;

    if (auto to_remove =
            std::find(keys_[old_count].begin(), keys_[old_count].end(), key);
        to_remove != keys_[old_count].end()) {
      keys_[old_count].erase(to_remove);
    }
    if (keys_[old_count].empty()) {
      keys_.erase(old_count);
    }

    if (counts_[key] == 0) {
      counts_.erase(key);
      return;
    }

    keys_[counts_[key]].push_front(key);
  }

  std::string getMaxKey() {
    if (keys_.empty()) {
      return "";
    }
    return keys_.rbegin()->second.front();
  }

  std::string getMinKey() {
    if (keys_.empty()) {
      return "";
    }
    return keys_.begin()->second.front();
  }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

TEST(AllOOne, Example) {
  AllOne allOne;
  allOne.inc("hello");
  allOne.inc("hello");
  ASSERT_EQ(allOne.getMaxKey(), "hello");
  ASSERT_EQ(allOne.getMinKey(), "hello");
  allOne.inc("leet");
  ASSERT_EQ(allOne.getMaxKey(), "hello");
  ASSERT_EQ(allOne.getMinKey(), "leet");
}
