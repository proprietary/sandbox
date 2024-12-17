#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <array>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "tools/cpp/runfiles/runfiles.h"

namespace {
::bazel::tools::cpp::runfiles::Runfiles* runfiles;
std::string INPUT_FILE{"_main/advent_of_code/2024/day_15_input.txt"};
std::string EXAMPLE = R"(##########
#..O..O.O#
#......O.#
#.OO..O.O#
#..O@..O.#
#O#..O...#
#O..O..O.#
#.OO.O.OO#
#....O...#
##########

<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^
vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v
><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<
<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^
^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><
^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^
>^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^
<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>
^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>
v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^)";

enum class Move : int {
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3,
};

constexpr auto move_dir(const Move m) -> std::pair<int, int> {
  constexpr std::array<std::pair<int, int>, 4> directions{
      std::pair<int, int>{-1, 0},
      std::pair<int, int>{1, 0},
      std::pair<int, int>{0, -1},
      std::pair<int, int>{0, 1},
  };
  return directions[static_cast<int>(m)];
}

using Map = std::vector<std::string>;
using Moves = std::vector<Move>;
using Parsed = std::pair<Map, Moves>;

auto parse(std::istream& is) -> Parsed {
  Map map;
  Moves moves;
  std::string line;
  while (std::getline(is, line)) {
    if (line.empty()) break;
    map.push_back(line);
  }
  while (std::getline(is, line)) {
    for (const auto c : line) {
      switch (c) {
        case '^':
          moves.push_back(Move::UP);
          break;
        case 'v':
          moves.push_back(Move::DOWN);
          break;
        case '<':
          moves.push_back(Move::LEFT);
          break;
        case '>':
          moves.push_back(Move::RIGHT);
          break;
        default:
          assert(false);
      }
    }
  }
  return {map, moves};
}

auto solve_part_1(Parsed input) -> uint64_t {
  uint64_t res = 0;
  auto& [map, moves] = input;
  const int R = map.size();
  const int C = map[0].size();
  int y = 0, x = 0;
  for (; y < R; ++y) {
    for (x = 0; x < C; ++x) {
      if (map[y][x] == '@') {
        goto found_robot;
      }
    }
  }
found_robot:
  auto in_bounds = [&R, &C](int rr, int cc) {
    return rr >= 0 && rr < R && cc >= 0 && cc < C;
  };

  std::function<bool(int, int, int, int)> push_boxes = [&](int r, int c, int dr,
                                                           int dc) -> bool {
    int nr = r + dr;
    int nc = c + dc;
    if (!in_bounds(nr, nc)) return false;
    if (map[nr][nc] == '#') {
      return false;
    } else if (map[nr][nc] == 'O') {
      if (!push_boxes(nr, nc, dr, dc)) return false;
    } else if (map[nr][nc] != '.' && map[nr][nc] != '@') {
      return false;
    }
    map[nr][nc] = 'O';
    map[r][c] = '.';
    return true;
  };

  for (auto m : moves) {
    auto [dr, dc] = move_dir(m);
    const int nr = y + dr;
    const int nc = x + dc;
    if (!in_bounds(nr, nc)) {
      continue;
    }
    if (map[nr][nc] == '#') {
      continue;
    } else if (map[nr][nc] == '.') {
      map[y][x] = '.';
      map[nr][nc] = '@';
      y = nr;
      x = nc;
    } else if (map[nr][nc] == 'O') {
      if (push_boxes(nr, nc, dr, dc)) {
        map[y][x] = '.';
        map[nr][nc] = '@';
        y = nr;
        x = nc;
      }
    }
  }

  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      if (map[r][c] == 'O') {
        res += r * 100 + c;
      }
    }
  }
  return res;
}

bool move2b(std::string line, int y, Move m, std::vector<std::string>& map) {
  const int R = (int)map.size();
  const int C = (int)map[0].size();
  auto [dy, _] = move_dir(m);
  int ny = y + dy;

  if (ny < 0 || ny >= R) return false;

  for (int x = 0; x < C; x++) {
    if (line[x] != '.') {
      if (map[ny][x] == '#') return false;
    }
  }

  std::string newline(C, '.');
  for (int x = 0; x < C; x++) {
    if (line[x] != '.') {
      newline[x] = map[ny][x];
      if (newline[x] == '[') {
        newline[x + 1] = map[ny][x + 1];
      } else if (newline[x] == ']') {
        newline[x - 1] = map[ny][x - 1];
      }
    }
  }

  if (newline.find('[') != std::string::npos) {
    if (!move2b(newline, ny, m, map)) return false;
  }

  for (int x = 0; x < C; x++) {
    if (line[x] != '.') {
      map[ny][x] = map[y][x];
      map[y][x] = '.';
    }
  }

  return true;
}

void move2(int y, int x, Move m, std::vector<std::string>& map) {
  const int R = map.size();
  const int C = map[0].size();
  auto [dy, dx] = move_dir(m);

  int ynb = y + dy;
  int xnb = x + dx;

  if (ynb < 0 || ynb >= R || xnb < 0 || xnb + 1 >= C) return;
  if (map[ynb][xnb] == '#' && map[ynb][xnb + 1] == '#') return;

  if (m == Move::LEFT || m == Move::RIGHT) {
    if (map[ynb][xnb] == '[' || map[ynb][xnb] == ']') {
      move2(ynb, xnb, m, map);
    }
    if (map[ynb][xnb] == '.') {
      map[ynb][xnb] = map[y][x];
      map[y][x] = '.';
    }
    return;
  }

  if (map[ynb][xnb] == '[' || map[ynb][xnb] == ']') {
    std::string line(C, '.');
    line[xnb] = map[ynb][xnb];
    if (line[xnb] == '[' && xnb + 1 < C) {
      line[xnb + 1] = map[ynb][xnb + 1];
    } else if (line[xnb] == ']' && xnb - 1 >= 0) {
      line[xnb - 1] = map[ynb][xnb - 1];
    }
    move2b(line, ynb, m, map);
  }

  if (map[ynb][xnb] == '.') {
    map[ynb][xnb] = map[y][x];
    map[y][x] = '.';
  }
}

auto solve_part_2(Parsed input) -> uint64_t {
  auto& [map_orig, moves] = input;
  auto map = map_orig;

  for (int i = 0; i < (int)map.size(); ++i) {
    std::string row;
    for (int j = 0; j < (int)map[i].size(); ++j) {
      const char c = map[i][j];
      if (c == '#')
        row += "##";
      else if (c == 'O')
        row += "[]";
      else if (c == '.')
        row += "..";
      else if (c == '@')
        row += "@.";
      else
        assert(false);
    }
    map[i] = row;
  }

  const int R = (int)map.size();
  const int C = (int)map[0].size();

  int robot_r = -1, robot_c = -1;
  for (int i = 0; i < R && robot_r == -1; ++i) {
    for (int j = 0; j + 1 < C && robot_r == -1; ++j) {
      if (map[i][j] == '@' && map[i][j + 1] == '.') {
        robot_r = i;
        robot_c = j;
      }
    }
  }

  for (auto m : moves) {
    move2(robot_r, robot_c, m, map);

    bool found = false;
    for (int rr = 0; rr < R && !found; rr++) {
      for (int cc = 0; cc + 1 < C && !found; cc++) {
        if (map[rr][cc] == '@') {
          robot_r = rr;
          robot_c = cc;
          found = true;
        }
      }
    }
  }

  // Calculate result
  uint64_t res = 0;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j + 1 < C; j++) {
      if (map[i][j] == '[' && map[i][j + 1] == ']') {
        res += i * 100 + j;
      }
    }
  }

  return res;
}

TEST(Part1, Example) {
  std::istringstream input{EXAMPLE};
  const auto got = solve_part_1(parse(input));
  ASSERT_EQ(got, 10092);
}

TEST(Part1, Input) {
  std::ifstream input{runfiles->Rlocation(INPUT_FILE)};
  const auto got = solve_part_1(parse(input));
  ASSERT_EQ(got, 1457740);
}

TEST(Part2, Example) {
  std::istringstream input{EXAMPLE};
  const auto got = solve_part_2(parse(input));
  ASSERT_EQ(got, 9021);
}

TEST(Part2, Input) {
  std::ifstream input{runfiles->Rlocation(INPUT_FILE)};
  const auto got = solve_part_2(parse(input));
  ASSERT_EQ(got, 1467145);
}
}  // namespace

int main(int argc, char* argv[]) {
  runfiles = ::bazel::tools::cpp::runfiles::Runfiles::Create(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
  delete listeners.Release(listeners.default_result_printer());
  assert(RUN_ALL_TESTS() == 0);
  const auto parsed = parse(std::cin);
  const auto part_1 = solve_part_1(parsed);
  fmt::println("{}", part_1);
  const auto part_2 = solve_part_2(parsed);
  fmt::println("{}", part_2);
  return 0;
}
