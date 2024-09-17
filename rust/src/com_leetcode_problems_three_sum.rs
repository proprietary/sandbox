#![allow(dead_code)]

struct Solution;

impl Solution {
    pub fn three_sum(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut triplets = std::collections::HashSet::<(i32, i32, i32)>::new();
        let mut arr = nums.clone();
        arr.sort();
        for i in 0..arr.len() {
            let target = -arr[i];
            let mut j = i + 1;
            let mut k = arr.len() - 1;
            while j < k {
                let sum = arr[j] + arr[k];
                if sum < target {
                    j += 1;
                } else if sum > target {
                    k -= 1;
                } else {
                    let triplet = (arr[i], arr[j], arr[k]);
                    triplets.insert(triplet);
                    while j < k && arr[j] == triplet.1 {
                        j += 1;
                    }
                    while j < k && arr[k] == triplet.2 {
                        k -= 1;
                    }
                }
            }
        }
        let mut ans: Vec<Vec<i32>> = triplets
            .into_iter()
            .map(|(a, b, c)| vec![a, b, c])
            .collect();
        ans.sort();
        ans
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn example1() {
        assert_eq!(
            vec![vec![-1, -1, 2], vec![-1, 0, 1]],
            Solution::three_sum(vec![-1, 0, 1, 2, -1, -4])
        );
    }

    #[test]
    fn example2() {
        assert_eq!(Vec::<Vec<i32>>::new(), Solution::three_sum(vec![0, 1, 1]));
    }

    #[test]
    fn example3() {
        assert_eq!(vec![vec![0, 0, 0]], Solution::three_sum(vec![0, 0, 0]));
    }

    #[test]
    fn example4() {
        assert_eq!(
            vec![vec![-2, 0, 2], vec![-2, 1, 1]],
            Solution::three_sum(vec![-2, 0, 1, 1, 2])
        );
    }

    #[test]
    fn example5() {
        assert_eq!(
            vec![
                vec![-4, -2, 6],
                vec![-4, 0, 4],
                vec![-4, 1, 3],
                vec![-4, 2, 2],
                vec![-2, -2, 4],
                vec![-2, 0, 2]
            ],
            Solution::three_sum(vec![-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6])
        );
    }
}
