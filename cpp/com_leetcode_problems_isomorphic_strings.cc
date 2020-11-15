#include <string>
#include <vector>

class Solution {
    public:
	bool isIsomorphic(std::string s, std::string t) {
		if (s.length() != t.length()) {
			return false;
		}
		if (s.length() == 0) {
			return true;
		}
		constexpr unsigned char dummy =
		    static_cast<unsigned char>(1 << 8);
		constexpr size_t max_char = (1 << 8) - 1;
		std::vector<unsigned char> m_1(max_char, dummy);
		std::vector<unsigned char> m_2(max_char, dummy);
		for (size_t i = 0; i < s.length(); ++i) {
			if (m_1[s[i]] == dummy) {
				m_1[s[i]] = t[i];
			}
			if (m_2[t[i]] == dummy) {
				m_2[t[i]] = s[i];
			}
			if (m_1[s[i]] != t[i] || m_2[t[i]] != s[i]) {
				return false;
			}
		}
		return true;
	}
};

#include <gtest/gtest.h>

TEST(Test, Test) {
	ASSERT_EQ(true, Solution().isIsomorphic("egg", "add"));
	ASSERT_EQ(false, Solution().isIsomorphic("foo", "bar"));
	ASSERT_EQ(true, Solution().isIsomorphic("paper", "title"));
	ASSERT_EQ(false, Solution().isIsomorphic("ab", "aa"));
}
