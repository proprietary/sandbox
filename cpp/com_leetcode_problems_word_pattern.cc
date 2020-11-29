#include <bits/stdc++.h>

class Solution {
    public:
	bool wordPattern(std::string pattern, std::string s) {
		size_t word_count = 1 + std::count(s.begin(), s.end(), ' ');
		if (word_count != pattern.length()) {
			return false;
		}
		std::unordered_map<std::string::value_type, std::string> m;
		std::unordered_map<std::string, std::string::value_type> n;
		m.reserve(pattern.length());
		n.reserve(pattern.length());
		auto word_begin = s.begin();
		auto word_end = word_begin;
		size_t pattern_idx = 0;
		while (word_begin != s.end() && word_end != s.end()) {
			word_end = word_begin;
			while (word_end != s.end() && *word_end != ' ') {
				++word_end;
			}
			std::string word;
			word.insert(word.cbegin(), word_begin, word_end);
			auto const patt = pattern[pattern_idx];
			auto const pattern_found = m.find(patt) != m.end();
			auto const word_found = n.find(word) != n.end();
			if (pattern_found && word_found) {
				if (m[patt] != word || n[word] != patt) {
					return false;
				}
			} else if (!pattern_found && !word_found) {
				m[patt] = word;
				n[word] = patt;
			} else {
				return false;
			}
			pattern_idx += 1;
			word_begin = word_end + 1;
		}
		return true;
	}
};

#include <gtest/gtest.h>

TEST(Test, Test1) {
	EXPECT_EQ(true, Solution().wordPattern("abba", "dog cat cat dog"));
	EXPECT_EQ(false, Solution().wordPattern("abba", "dog cat cat fish"));
	EXPECT_EQ(false, Solution().wordPattern("abba", "dog dog dog dog"));
	EXPECT_EQ(false, Solution().wordPattern("aaaa", "dog cat dog dog"));
	EXPECT_EQ(false, Solution().wordPattern("jquery", "jquery"));
	EXPECT_EQ(false, Solution().wordPattern("aaa", "aa aa aa aa"));
}
