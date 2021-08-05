struct Solution {}

impl Solution {
	pub fn majority_element_0(nums: Vec<i32>) -> i32 {
		let mut nums_ = nums.clone();
		nums_.sort();
		let mut p: i32 = nums_[0];
		let mut mx: i32 = p;
		let mut mx_cnt: usize = 0;
		let mut cnt: usize = 1;
		// println!("nums_: {:?}, len: {}", nums_, nums_.len());
		for m in nums_.iter().skip(1) {
			if p == *m {
				cnt += 1;
			} else {
				// println!("cnt: {}, p: {}, mx_cnt: {}, mx: {}", cnt, p, mx_cnt, mx);
				if cnt > mx_cnt {
					mx_cnt = cnt;
					mx = p;
				}
				cnt = 1;
			}
			p = *m;
		}
		if cnt > mx_cnt {
			mx = p;
			mx_cnt = cnt;
		}
		// assert!(mx_cnt > (nums.len() / 2));
		mx
	}

	pub fn majority_element_1(nums: Vec<i32>) -> i32 {
		let mut nums_ = nums.clone();
		nums_.sort();
		nums_[nums.len() / 2]
	}

	pub fn majority_element(nums: Vec<i32>) -> i32 {
		let mut count: i32 = 0;
		let mut candidate: i32 = 0;
		for n in nums.iter() {
			if count == 0 {
				candidate = *n;
			}
			if *n == candidate {
				count += 1;
			} else {
				count -= 1;
			}
		}
		candidate
	}
}

#[cfg(test)]
mod test {
	use super::*;

	#[test]
	fn example_1() {
		assert_eq!(Solution::majority_element(vec![3,2,3]), 3);
	}

	#[test]
	fn example_2() {
		assert_eq!(Solution::majority_element(vec![2,2,1,1,1,2,2]), 2);
	}

	#[test]
	fn example_3() {
		assert_eq!(Solution::majority_element(vec![6,5,5]), 5);
	}

	#[test]
	fn example_4() {
		assert_eq!(Solution::majority_element(vec![-1,1,1,1,2,1]), 1);
	}
}
