#pragma once

#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
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

class BoolDeserializer {
  public:
  bool deserialize(std::string_view str) {
    trim(str);
    if (str == "true") {
      return true;
    } else if (str == "false") {
      return false;
    }
    throw std::runtime_error("Invalid boolean value");
  }
};

using IntVecParser = VecParser<int, IntDeserializer>;
using StringVecParser = VecParser<std::string, StringDeserializer>;
using BoolVecParser = VecParser<bool, BoolDeserializer>;

template <typename T, size_t N>
struct NestedVector {
  using type = std::vector<typename NestedVector<T, N - 1>::type>;
};

template <typename T>
struct NestedVector<T, 0> {
  using type = T;
};

template <typename T, size_t N>
using NestedVector_t = typename NestedVector<T, N>::type;

class NestedVecParser {
  std::string_view str;
  size_t pos;

  public:
  constexpr NestedVecParser(std::string_view s) : str(s), pos(0) {}

  template <typename T = int>
  constexpr auto parse() {
    skipWhitespace();
    auto result = parseNode<T, 0>();
    skipWhitespace();
    if (pos != str.size()) {
      throw std::runtime_error("Unexpected characters at the end of input");
    }
    return result;
  }

  private:
  constexpr void skipWhitespace() {
    while (pos < str.size() &&
       std::isspace(static_cast<unsigned char>(str[pos]))) {
      ++pos;
    }
  }

  constexpr bool match(char ch) {
    if (pos < str.size() && str[pos] == ch) {
      ++pos;
      return true;
    }
    return false;
  }

  constexpr char peek() const {
    if (pos < str.size()) {
      return str[pos];
    }
    return '\0';
  }

  template <typename T, size_t Depth>
  constexpr auto parseNode() -> NestedVector_t<T, Depth> {
    skipWhitespace();
    if (match('[')) {
      return parseList<T, Depth + 1>();
    } else {
      return parseInt<T>();
    }
  }

  template <typename T>
  constexpr T parseInt() {
    skipWhitespace();
    bool negative = false;
    if (match('-')) {
      negative = true;
    }
    int value = 0;
    bool has_digits = false;
    while (pos < str.size() &&
       std::isdigit(static_cast<unsigned char>(str[pos]))) {
      has_digits = true;
      value = value * 10 + (str[pos++] - '0');
    }
    if (!has_digits) {
      throw std::runtime_error("Expected integer");
    }
    return negative ? -value : value;
  }

  template <typename T, size_t Depth>
  constexpr auto parseList() {
    using ElementType = NestedVector_t<T, Depth - 1>;
    std::vector<ElementType> elements;
    skipWhitespace();
    if (match(']')) {
      return elements;
    }
    while (true) {
      elements.push_back(parseNode<T, Depth - 1>());
      skipWhitespace();
      if (match(',')) {
    continue;
      } else if (match(']')) {
    break;
      } else {
    throw std::runtime_error("Expected ',' or ']'");
      }
    }
    return elements;
  }
};

template <typename T>
class ListElementNode {
public:
  using value_type = std::vector<std::variant<std::vector<ListElementNode>, T>>;
  value_type value;

  const std::vector<ListElementNode>& as_vec() const {
    return std::get<std::vector<ListElementNode>>(value);
  }

  const T& as_value() const { return std::get<T>(value); }

  template <typename V>
  auto operator==(const std::vector<V>& other) {
    if (std::holds_alternative<T>(value)) {
      return false;
    }
    if (as_vec().size() != other.size()) {
      return false;
    }
    for (size_t i = 0; i < other.size(); i++) {
      if (std::holds_alternative<T>(as_vec()[i].value) && as_vec()[i].as_value() != other[i]) {
        return false;
      }
      if (as_vec()[i].as_vec() != other[i]) {
        return false;
      }
    }
    return true;
  }

  ListElementNode(T v) : value(v) {}
  ListElementNode(std::vector<ListElementNode> v) : value(std::move(v)) {}
};

template <typename T, DeserializerFn<T> Deser>
auto parse_list(std::string_view str) -> std::vector<ListElementNode<T>>  {
  Deser deserializer;
  std::vector<ListElementNode<T>> result;
  auto it = str.begin();
  auto end = str.end();
  if (*it++ != '[') {
    throw std::runtime_error("Expected '['");
  }
  while (it != end && *it != ']') {
    if (*it == '[') {
      result.emplace_back(parse_list<T, Deser>(std::string_view{it, end}));
      it++;
    } else {
      auto comma = std::find(it, end, ',');
      if (comma == end) {
        throw std::runtime_error("Expected ',' or ']'");
      }
      result.emplace_back(deserializer.deserialize(std::string_view{it, comma}));
      it = comma + 1;
    }
  }
}

auto operator==(const ListElementNode<int>& lhs,
                const ListElementNode<int>& rhs) -> bool;

// template <typename T, std::size_t N>
// constexpr auto operator""_nested_vector(const char (&str)[N]) {
//   constexpr std::string_view sv(str, N - 1);  // Exclude null terminator
//   NestedVecParser parser(sv);
//   return parser.parse<T>();
// }

std::vector<std::vector<std::string>> partition_test_cases(
    std::string_view src, int lines_per_test_case);
