#![allow(dead_code)]

struct Solution;

impl Solution {
    pub fn longest_common_prefix(arr1: Vec<i32>, arr2: Vec<i32>) -> i32 {
        let mut s = std::collections::HashSet::<i32>::new();
        for n in arr1 {
            let mut m = n;
            while m > 0 {
                s.insert(m);
                m /= 10;
            }
        }
        let mut best: i32 = 0;
        for n in arr2 {
            let mut m: i32 = n;
            while m > 0 && !s.contains(&m) {
                m /= 10;
            }
            if m != 0 {
                best = std::cmp::max(best, (m.ilog10() as i32) + 1);
            }
        }
        return best;
    }
}

#[cfg(test)]
mod test {
    use super::Solution;

    #[test]
    fn examples() {
        assert_eq!(
            3,
            Solution::longest_common_prefix(vec![1, 10, 100], vec![1000])
        );
        assert_eq!(
            0,
            Solution::longest_common_prefix(vec![1, 2, 3], vec![4, 4, 4])
        );
    }
}
