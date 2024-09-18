#pragma once

#include <string>
#include <string_view>
#include <vector>

template <typename D, typename T>
concept DeserializerFn = requires(D d, std::string_view str) {
  { d.deserialize(str) } -> std::same_as<T>;
};

template <typename T, DeserializerFn<T> Deser>
class VecParser {
  private:
  std::string_view str_;
  std::vector<T> vec_;
  size_t pos_ = 0;
  Deser deserializer_;

  char peek() { return pos_ < str_.length() ? str_[pos_] : '\0'; }

  char consume() { return pos_ < str_.length() ? str_[pos_++] : '\0'; }

  T parse_value() {
    std::string value;
    while (peek() != ',' && peek() != ']' && peek() != '\0') {
      value += consume();
    }
    return deserializer_.deserialize(value);
  }

  std::vector<T> parse_subvec() {
    std::vector<T> subvec;
    consume();  // consume '['
    while (peek() != ']' && peek() != '\0') {
      if (peek() == '[') {
        subvec.push_back(parse_subvec());
      } else {
        subvec.push_back(parse_value());
        if (peek() == ',') {
          consume();
        }
      }
    }
    consume();  // consume ']'
    return subvec;
  }

  public:
  VecParser(std::string_view str) : str_(str) {}

  std::vector<T> parse() {
    consume();  // consume '['
    while (peek() != ']' && peek() != '\0') {
      vec_.push_back(parse_value());
      if (peek() == ',') {
        consume();
      }
    }
    consume();  // consume ']'
    return vec_;
  }
};

class IntDeserializer {
  public:
  int deserialize(std::string_view str) { return std::stoi(std::string(str)); }
};

void ltrim(std::string_view& src);

void rtrim(std::string_view& src);

void trim(std::string_view& src);

class StringDeserializer {
  public:
  std::string deserialize(std::string_view str) {
    trim(str);
    if (str.front() == '"' && str.back() == '"') {
      return std::string(str.substr(1, str.length() - 2));
    }
    return std::string(str);
  }
};

using IntVecParser = VecParser<int, IntDeserializer>;
using StringVecParser = VecParser<std::string, StringDeserializer>;

std::vector<std::vector<std::string>> partition_test_cases(
    std::string_view src, int lines_per_test_case);
