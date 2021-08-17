// https://leetcode.com/problems/di-string-match/

impl Solution {
    pub fn di_string_match(s: String) -> Vec<i32> {
		let mut v = Vec::<i32>::with_capacity(s.len() + 1);
		v.fill(0);
		let mut i = v.len() - 1;
        for ch in s.chars().into_iter().rev() {
			if *ch == 'I' {
				v[i] = 
		}
		vec![]
    }
}

struct Solution {}
