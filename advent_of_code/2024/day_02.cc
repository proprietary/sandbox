#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {
bool is_safe(const std::vector<int>& report) {
  int prev_difference = 0;
  bool prev_difference_initialized = false;
  auto prev = report.begin();
  for (auto cur = std::next(prev); cur != report.end(); ++cur) {
    const int difference = *cur - *prev;
    const int abs_difference = std::abs(difference);
    if (abs_difference == 0 || abs_difference > 3) {
      return false;
    }
    if (prev_difference_initialized &&
        (difference > 0) != (prev_difference > 0)) {
      return false;
    }
    prev_difference = difference;
    prev_difference_initialized = true;
    prev = cur;
  }
  return true;
}

bool is_safe_with_toleration(const std::vector<int>& report) {
  auto report_copy = report;
  for (int i = 0; i < report.size(); ++i) {
    report_copy.erase(report_copy.begin() + i);
    if (is_safe(report_copy)) {
      return true;
    }
    report_copy.insert(report_copy.begin() + i, report[i]);
  }
  return false;
}
}  // namespace

int main(int argc, char* argv[], char* envp[]) {
  uint64_t safe_reports_1 = 0, safe_reports_2 = 0;
  std::vector<int> report;

  std::string line;
  while (std::getline(std::cin, line)) {
    std::stringstream ss{line};
    int level;
    while (ss >> level) {
      report.push_back(level);
    }

    if (is_safe(report)) {
      safe_reports_1++;
      safe_reports_2++;
    } else if (is_safe_with_toleration(report)) {
      safe_reports_2++;
    }

    report.clear();
  }

  std::cout << safe_reports_1 << '\n' << safe_reports_2 << '\n';

  return 0;
}
