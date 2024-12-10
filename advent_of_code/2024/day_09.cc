#include <gtest/gtest.h>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <string_view>
#include <utility>
#include <cassert>
#include <variant>

#include <fmt/format.h>
#include <fmt/std.h>
#include <fmt/ranges.h>
#include <fmt/chrono.h>
#include <fmt/color.h>


namespace {
  struct Empty {};
  struct File {
    int file_id;
  };
  using Block = std::variant<File, Empty>;
  auto expand_line(const std::string& line) -> std::vector<Block> {
    std::vector<Block> expanded_line;
    int file_id = 0;
    bool file_flag = true;
    for (const char c : line) {
      const int n = c - '0';
      if (file_flag) {
        for (int i = 0; i < n; ++i) {
          expanded_line.emplace_back(File{file_id});
        }
        ++file_id;
      } else {
        for (int i = 0; i < n; ++i) {
          expanded_line.emplace_back(Empty{});
        }
      }
      file_flag = !file_flag;
    }
    return expanded_line;
  }

  auto solve_part_1(std::vector<Block> expanded_line) -> uint64_t {
    uint64_t part_1 = 0;
    size_t r = expanded_line.size() - 1;
    size_t l = 0;
    while (l < r) {
      while (l < expanded_line.size() && std::holds_alternative<File>(expanded_line[l])) {
        ++l;
      }
      while (r < static_cast<size_t>(-1) && std::holds_alternative<Empty>(expanded_line[r])) {
        --r;
      }
      if (l >= r) {
        break;
      }
      std::swap(expanded_line[l], expanded_line[r]);
    }
    for (size_t i = 0; i < expanded_line.size() && !std::holds_alternative<Empty>(expanded_line[i]); ++i) {
      const auto f = std::get<File>(expanded_line[i]);
      part_1 += f.file_id * i;
    }
    return part_1;
  }

  std::vector<int> parse_disk(std::string_view s, int &num_files) {
    std::vector<int> blocks;
    num_files = 0;
    bool file_next = true;
    int file_id = 0;
    for (int i = 0; i < (int)s.size(); i++) {
      int length = s[i] - '0';
      if (file_next) {
        if (length > 0) {
          for (int b = 0; b < length; b++) {
            blocks.push_back(file_id);
          }
          file_id++;
        }
        file_next = false;
      } else {
        if (length > 0) {
          for (int b = 0; b < length; b++) {
            blocks.push_back(-1);
          }
        }
        file_next = true;
      }
    }
    num_files = file_id;
    return blocks;
  }

  uint64_t compute_checksum(const std::vector<int> &blocks) {
    uint64_t checksum = 0;
    for (uint64_t i = 0; i < blocks.size(); i++) {
      if (blocks[i] >= 0) {
        checksum += i * blocks[i];
      }
    }
    return checksum;
  }

  auto solve_part_2(std::string_view line) -> uint64_t {
    struct FileInfo {
      int start = -1;
      int end = -1;
      int length = 0;
    };
    int num_files;
    std::vector<int> blocks = parse_disk(line, num_files);
    std::vector<FileInfo> files(num_files);

    for (int i = 0; i < blocks.size(); i++) {
      int fid = blocks[i];
      if (fid >= 0) {
        if (files[fid].start == -1) {
          files[fid].start = i;
        }
        files[fid].end = i;
        files[fid].length++;
      }
    }

    for (int fid = num_files - 1; fid >= 0; fid--) {
      FileInfo &finfo = files[fid];
      if (finfo.start == -1) {
        continue;
      }
      int flen = finfo.length;
      int fstart = finfo.start;

      int best_start = -1;
      int run_start = -1;
      for (int i = 0; i < fstart; i++) {
        if (blocks[i] == -1) {
          if (run_start == -1) run_start = i;
        } else {
          // end of a free run
          if (run_start != -1) {
            int runLen = i - run_start;
            if (runLen >= flen) {
              // This run can hold the file
              best_start = run_start;
              break; // first suitable run we find
            }
            run_start = -1;
          }
        }
      }
      if (best_start == -1 && run_start != -1) {
        int runLen = fstart - run_start;
        if (runLen >= flen) {
          best_start = run_start;
        }
      }

      if (best_start != -1) {
        int fend = finfo.end;

        std::vector<int> file_blocks;
        for (int i = fstart; i <= fend; i++) {
          file_blocks.push_back(blocks[i]);
        }

        for (int i = fstart; i <= fend; i++) {
          blocks[i] = -1;
        }

        for (int i = 0; i < flen; i++) {
          blocks[best_start + i] = file_blocks[i];
        }

        finfo.start = best_start;
        finfo.end = best_start + flen - 1;
      }
    }
    return compute_checksum(blocks);
  }



  auto solve(std::istream& input) -> std::pair<uint64_t, uint64_t> {
    uint64_t part_1 = 0, part_2 = 0;
    std::string line;
    std::getline(input, line);
    auto expanded_line = expand_line(line);
    part_1 = solve_part_1(expanded_line);
    part_2 = solve_part_2(line);
    return {part_1, part_2};
  }

  constexpr std::string EXAMPLE = "2333133121414131402";

  TEST(Part1, ExpandLine) {
    std::string as_string;
    const auto expanded_line = expand_line(EXAMPLE);
    for (const auto block : expanded_line) {
      if (std::holds_alternative<Empty>(block)) {
        as_string.push_back('.');
      } else {
        const auto f = std::get<File>(block);
        as_string += std::to_string(f.file_id);
      }
    }
    ASSERT_EQ("00...111...2...333.44.5555.6666.777.888899", as_string);
  }

  TEST(Part1, Example) {
    std::istringstream input{EXAMPLE};
    const auto [part_1, _] = solve(input);
    ASSERT_EQ(part_1, 1928);
  }

  TEST(Part2, Example) {
    std::istringstream input{EXAMPLE};
    const auto [_, part_2] = solve(input);
    ASSERT_EQ(part_2, 2858);
  }
} // namespace

int main(int argc, char *argv[], char *envp[]) {
  ::testing::InitGoogleTest(&argc, argv);
  assert(RUN_ALL_TESTS() == 0);
  const auto [part_1, part_2] = solve(std::cin);
  fmt::println("{}\n{}", part_1, part_2);
  return 0;
}
