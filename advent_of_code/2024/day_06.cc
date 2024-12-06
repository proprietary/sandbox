#include <array>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
constexpr std::array<std::array<int, 2>, 4> directions{
    std::array<int, 2>{-1, 0},  // up
    std::array<int, 2>{0, 1},   // right
    std::array<int, 2>{1, 0},   // down
    std::array<int, 2>{0, -1},  // left
};
auto find_guard(const std::vector<std::string>& map) -> std::pair<int, int> {
  int guard_x = 0, guard_y = 0;
  for (; guard_y < map.size(); ++guard_y) {
    guard_x = 0;
    for (; guard_x < map[guard_y].size(); ++guard_x) {
      if (map[guard_y][guard_x] == '^') {
        return {guard_y, guard_x};
      }
    }
  }
  throw std::runtime_error{"No guard found"};
}

auto sim(std::vector<std::string> map, int guard_x, int guard_y)
    -> std::pair<int, bool> {
  const int rows = map.size();
  const int cols = map[0].size();
  std::vector<std::vector<std::array<bool, 4>>> visited(
      rows, std::vector<std::array<bool, 4>>(
                cols, std::array<bool, 4>{false, false, false, false}));
  visited[guard_y][guard_x][0] = true;
  int visited_count = 0;
  int direction = 0;
  while (guard_y > -1 || guard_x > -1 || guard_y < rows || guard_x < cols) {
    const int next_x = guard_x + directions[direction][1];
    const int next_y = guard_y + directions[direction][0];
    if (next_y < 0 || next_x < 0 || next_y >= rows || next_x >= cols) {
      break;
    }
    switch (map[next_y][next_x]) {
      case 'X':
        guard_x += directions[direction][1];
        guard_y += directions[direction][0];
        break;
      case '^':
      case '.':
        guard_x += directions[direction][1];
        guard_y += directions[direction][0];
        visited_count++;
        break;
      case '#':
        direction = (direction + 1) % 4;
        if (visited[guard_y][guard_x][direction]) {
          return {visited_count, true};
        } else {
          visited[guard_y][guard_x][direction] = true;
        }
        break;
      default:
        assert(false);
    }
    map[guard_y][guard_x] = 'X';
  }
  return {visited_count, false};
}
}  // namespace

int main(int argc, char* argv[]) {
  std::vector<std::string> map;
  std::string line;
  while (std::getline(std::cin, line)) {
    map.push_back(line);
  }
  auto map_pt_1 = map;
  const auto [guard_y, guard_x] = find_guard(map_pt_1);
  const auto [visited, _] = sim(map_pt_1, guard_x, guard_y);
  std::cout << visited << '\n';
  int ways = 0;
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[i].size(); ++j) {
      if (map[i][j] != '#' && !(i == guard_y && j == guard_x)) {
        auto map_copy = map;
        map_copy[i][j] = '#';
        const auto [_, has_cycle] = sim(map_copy, guard_x, guard_y);
        if (has_cycle) {
          ++ways;
        }
      }
    }
  }
  std::cout << ways << '\n';
  return 0;
}
