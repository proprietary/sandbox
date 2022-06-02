#![allow(dead_code)]

struct Solution;

impl Solution {
    pub fn two_sum_o_n_2(nums: Vec<i32>, target: i32) -> Vec<i32> {
        for i in 0..nums.len() {
            for j in i + 1..nums.len() {
                let sum = nums[i] + nums[j];
                if sum == target {
                    return vec![i as i32, j as i32];
                }
            }
        }
        unreachable!()
    }

    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut tbl = std::collections::HashSet::<i32>::new();

        for n in nums.iter() {
            tbl.insert(*n);
        }

        for i in 0..nums.len() {
            let difference: i32 = target - nums[i];
            if tbl.contains(&difference) {
                for j in i + 1..nums.len() {
                    if nums[j] == difference {
                        return vec![i as i32, j as i32];
                    }
                }
            }
        }

        unreachable!()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn examples() {
        assert_eq!(vec![0, 1], Solution::two_sum(vec![2, 7, 11, 15], 9));
        assert_eq!(vec![1, 2], Solution::two_sum(vec![3, 2, 4], 6));
        assert_eq!(vec![0, 1], Solution::two_sum(vec![3, 3], 6));
    }
}
