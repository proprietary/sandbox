#include <algorithm>
#include <cassert>
#include <charconv>
#include <iostream>
#include <ranges>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
bool is_valid(const std::unordered_map<int, std::set<int>>& rules_ltr,
              const std::vector<int>& pages) {
  std::vector<int> seen;
  for (const int page : pages) {
    if (rules_ltr.contains(page)) {
      for (const auto x : seen) {
        if (rules_ltr.at(page).contains(x)) {
          return false;
        }
      }
    }
    seen.push_back(page);
    std::push_heap(seen.begin(), seen.end());
  }
  return true;
}
}  // namespace

int main(int argc, char* argv[]) {
  std::unordered_map<int, std::set<int>> rules_ltr;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) break;
    const auto bar_pos = line.find('|');
    const int a = std::stoi(line.substr(0, bar_pos));
    const int b = std::stoi(line.substr(bar_pos + 1));
    rules_ltr[a].insert(b);
  }
  int part_1 = 0, part_2 = 0;
  while (std::getline(std::cin, line)) {
    std::vector<int> pages;
    for (auto part : std::ranges::split_view(line, ',')) {
      int a = 0;
      auto [p, ec] = std::from_chars(part.data(), part.data() + part.size(), a);
      assert(ec == std::errc{});
      pages.push_back(a);
    }
    if (is_valid(rules_ltr, pages)) {
      part_1 += pages[pages.size() / 2];
    } else {
      std::vector<int> corrected = pages;
      for (int i = 0; i < corrected.size(); ++i) {
        const auto t = corrected[i];
        const auto& l_rules = rules_ltr[corrected[i]];
        for (int j = 0; j < i; ++j) {
          if (l_rules.contains(corrected[j])) {
            corrected.erase(corrected.begin() + i);
            corrected.insert(corrected.begin() + j, t);
            i = j;
          }
        }
      }
      assert(is_valid(rules_ltr, corrected));
      part_2 += corrected[corrected.size() / 2];
    }
  }
  std::cout << part_1 << '\n' << part_2 << '\n';
  return 0;
}
