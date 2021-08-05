// https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/

impl Solution {
	pub fn count_prime_set_bits(left: i32, right: i32) -> i32 {
		let mut primes = 0;
		let mut i = left;
		while i <= right {
			if is_prime(popcnt(i)) {
				primes += 1;
			}
			i += 1;
		}
		primes
	}
}

fn is_prime(n: i32) -> bool {
	if n <= 3 {
		return n > 1;
	}
	if n % 2 == 0 || n % 3 == 0 {
		return false;
	}
	let mut i = 5;
	while (i * i) <= n {
		if n % i == 0 || n % (i + 2) == 0 {
			return false;
		}
		i += 6;
	}
	true
}

fn popcnt(n: i32) -> i32 {
	let mut m = n;
	let mut cnt = 0;
	while m > 0 {
		if m & 1 == 1 {
			cnt += 1;
		}
		m >>= 1;
	}
	cnt
}

struct Solution {}

#[cfg(test)]
mod test {
	use super::*;

	#[test]
	fn test_popcnt() {
		assert_eq!(1, popcnt(1));
		assert_eq!(1, popcnt(2));
		assert_eq!(3, popcnt(21));
	}
	#[test]
	fn example_1() {
		assert_eq!(4, Solution::count_prime_set_bits(6, 10));
	}
}
