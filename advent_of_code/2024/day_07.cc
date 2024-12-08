#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

namespace {

struct CalibrationEquation {
  uint64_t test_value;
  std::vector<uint64_t> calibrations;
};

template <typename Func>
concept Operator = requires(Func f, uint64_t a, uint64_t b) {
  { f(a, b) } -> std::convertible_to<uint64_t>;
};

auto parse(std::istream& is) -> std::vector<CalibrationEquation> {
  std::vector<CalibrationEquation> equations;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss{line};
    std::string num_as_str;
    std::vector<uint64_t> calibrations;

    std::getline(iss, num_as_str, ':');
    const uint64_t test_value = std::stoull(num_as_str);

    while (iss >> num_as_str) {
      calibrations.push_back(std::stoull(num_as_str));
    }
    equations.emplace_back(test_value, std::move(calibrations));
  }
  return equations;
}

template <Operator... Func>
auto can_evaluate(const CalibrationEquation& e, Func... operators) -> bool {
  std::vector<std::pair<decltype(e.calibrations.begin()), uint64_t>> s;
  if (e.calibrations.empty()) {
    return false;
  }
  s.emplace_back(e.calibrations.begin() + 1, e.calibrations[0]);
  while (!s.empty()) {
    const auto [it, acc] = s.back();
    s.pop_back();
    for (const uint64_t new_acc : {operators(acc, *it)...}) {
      const bool is_last = std::next(it) == e.calibrations.cend();
      if (is_last && new_acc == e.test_value) {
        return true;
      }
      if (!is_last && new_acc <= e.test_value) {
        s.emplace_back(std::next(it), new_acc);
      }
    }
  }
  return false;
}

auto solution(const std::vector<CalibrationEquation>& input)
    -> std::pair<uint64_t, uint64_t> {
  auto add = [](uint64_t a, uint64_t b) -> uint64_t { return a + b; };
  auto mul = [](uint64_t a, uint64_t b) -> uint64_t { return a * b; };
  auto concat = [](uint64_t a, uint64_t b) -> uint64_t {
    uint64_t multiplier = 1;
    uint64_t temp = b;
    if (temp == 0) {
      multiplier = 10;
    } else {
      while (temp != 0) {
        temp /= 10;
        multiplier *= 10;
      }
    }
    return a * multiplier + b;
  };
  uint64_t part_1 = 0, part_2 = 0;
  for (const auto& e : input) {
    if (can_evaluate(e, add, mul)) {
      part_1 += e.test_value;
      part_2 += e.test_value;
    } else if (can_evaluate(e, add, mul, concat)) {
      part_2 += e.test_value;
    }
  }
  return {part_1, part_2};
}

}  // namespace

int main(int argc, char* argv[], char* envp[]) {
  const auto equations = parse(std::cin);
  const auto [part_1, part_2] = solution(equations);
  std::cout << part_1 << '\n' << part_2 << '\n';
  return 0;
}
