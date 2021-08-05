// https://leetcode.com/problems/unique-paths-ii/

use std::collections::HashMap;
use std::hash::Hash;

#[derive(Hash, Eq, PartialEq, Clone, Copy, Debug)]
struct Point {
	x: usize,
	y: usize,
}

const OBSTACLE: i32 = 1;

impl Solution {
	pub fn unique_paths_with_obstacles(obstacle_grid: Vec<Vec<i32>>) -> i32 {
		if obstacle_grid[0][0] == 1 {
			return 0;
		}
		let mut m = HashMap::<Point, i32>::new();
		Self::paths(&mut m, &obstacle_grid, Point { x: 0, y: 0 })
	}

	fn paths(
		memo: &mut HashMap<Point, i32>,
		obstacle_grid: &Vec<Vec<i32>>,
		location: Point,
	) -> i32 {
		if memo.contains_key(&location) {
			return *memo.get(&location).unwrap();
		}
		let m = obstacle_grid[0].len();
		let n = obstacle_grid.len();
		if location.x == (m - 1) && location.y == (n - 1) {
			return if obstacle_grid[location.y][location.x] == OBSTACLE {
				0
			} else {
				1
			};
		}
		let mut paths_right: i32 = 0;
		if (location.x + 1) < m && obstacle_grid[location.y][location.x + 1] != OBSTACLE {
			paths_right = Self::paths(
				memo,
				&obstacle_grid,
				Point {
					x: location.x + 1,
					y: location.y,
				},
			);
		}
		let mut paths_down: i32 = 0;
		if (location.y + 1) < n && obstacle_grid[location.y + 1][location.x] != OBSTACLE {
			paths_down = Self::paths(
				memo,
				&obstacle_grid,
				Point {
					y: location.y + 1,
					x: location.x,
				},
			);
		}
		let res = paths_right + paths_down;
		memo.insert(location, res);
		res
	}
}

struct Solution {}

#[cfg(test)]
mod test {
	use super::*;

	#[test]
	fn example_1() {
		assert_eq!(
			2,
			Solution::unique_paths_with_obstacles(vec![
				vec![0, 0, 0],
				vec![0, 1, 0],
				vec![0, 0, 0]
			])
		);
	}

	#[test]
	fn example_2() {
		assert_eq!(
			1,
			Solution::unique_paths_with_obstacles(vec![vec![0, 1], vec![0, 0]])
		);
	}

	#[test]
	fn example_3() {
		assert_eq!(0, Solution::unique_paths_with_obstacles(vec![vec![1]]));
	}

	#[test]
	fn example_4() {
		assert_eq!(1, Solution::unique_paths_with_obstacles(vec![vec![0]]));
	}

	#[test]
	fn example_5() {
		assert_eq!(0, Solution::unique_paths_with_obstacles(vec![vec![1, 0]]));
	}
}
