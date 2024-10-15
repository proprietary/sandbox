#include "test_case_helper.hpp"

void ltrim(std::string_view& src) {
  while (!src.empty() && std::isspace(src.front())) {
    src.remove_prefix(1);
  }
}

void rtrim(std::string_view& src) {
  while (!src.empty() && std::isspace(src.back())) {
    src.remove_suffix(1);
  }
}

void trim(std::string_view& src) {
  ltrim(src);
  rtrim(src);
}

std::vector<std::vector<std::string>> partition_test_cases(
    std::string_view src, int lines_per_test_case) {
  trim(src);
  std::vector<std::vector<std::string>> test_cases;
  std::vector<std::string> current_test_case;
  std::string t;
  for (char c : src) {
    if (c == '\n') {
      current_test_case.push_back(t);
      t.clear();
      if (current_test_case.size() == lines_per_test_case) {
        test_cases.push_back(current_test_case);
        current_test_case.clear();
      }
    } else {
      t += c;
    }
  }
  if (!t.empty()) {
    current_test_case.push_back(t);
    if (current_test_case.size() != lines_per_test_case) {
      throw std::runtime_error("Not enough lines in the last test case");
    }
    test_cases.push_back(current_test_case);
  }
  return test_cases;
}

auto operator==(const ListElementNode<int>& lhs,
                const ListElementNode<int>& rhs) -> bool {
  if (lhs.value.size() != rhs.value.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.value.size(); i++) {
    if (lhs.value[i] != rhs.value[i]) {
      return false;
    }
  }
  return true;
}
