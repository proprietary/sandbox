#include <bits/stdc++.h>

class Solution {
  public:
  bool canConstruct(std::string ransomNote, std::string magazine) {
    constexpr auto num_letters = 26;
    unsigned int letters[num_letters];
    std::fill(std::begin(letters), std::end(letters), 0);
    for (auto i = 0; i < num_letters; ++i) {
      letters[i] = 0;
    }
    for (auto const ch : magazine) {
      letters[ch - 'a'] += 1;
    }
    for (auto const ch : ransomNote) {
      if (letters[ch - 'a']-- == 0) {
        return false;
      }
    }
    return true;
  }
};
