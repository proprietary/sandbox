// https://leetcode.com/problems/valid-perfect-square/

impl Solution {
    // pub fn is_perfect_square(num: i32) -> bool {
	// 	let f = num as f32;
	// 	let sr = f.sqrt() as i32;
	// 	sr * sr == num
    // }

	pub fn is_perfect_square(num: i32) -> bool {
		if num == 1 {
			return true;
		}
		let mut h: u64 = num as u64;
		let mut l: u64 = 1;
		while h >= l {
			let m = (h + l) / 2;
			let m2 = m * m;
			if m2 == num as u64 {
				return true;
			} else if m2 < num as u64 {
				l = m + 1;
			} else {
				h = m - 1;
			}
		}
		false
	}
}

struct Solution {}

#[cfg(test)]
mod test {
    use super::Solution;

    #[test]
    fn example_1() {
        assert_eq!(Solution::is_perfect_square(16), true);
    }

    #[test]
    fn example_2() {
        assert_eq!(Solution::is_perfect_square(14), false);
    }

	#[test]
	fn example_3() {
		assert_eq!(Solution::is_perfect_square(100), true);
	}

	#[test]
	fn example_4() {
		assert_eq!(Solution::is_perfect_square(1), true);
	}

	#[test]
	fn example_5() {
		assert_eq!(Solution::is_perfect_square(2147483647), false);
	}
}
