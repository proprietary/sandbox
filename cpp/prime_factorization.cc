// Project Euler problem 3 Largest prime factor
//
// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143?

#include <assert.h>
#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

auto prime_factors(uint64_t n) -> std::vector<uint64_t>;

auto largest_prime_factor(uint64_t n) -> uint64_t;

int main(int argc, char** argv) {
  // test with example: 13195
  {
    std::vector<uint64_t> expected = {5ULL, 7ULL, 13ULL, 29ULL};
    auto actual = prime_factors(13195ULL);
    assert(actual.size() == expected.size());
    for (int i = 0; i < expected.size(); ++i) assert(expected[i] == actual[i]);
    assert(29ULL == largest_prime_factor(13195ULL));
  }

  // try on input
  if (argc < 2) return EXIT_FAILURE;
  try {
    uint64_t input = std::stoll(std::string{argv[1]});
    auto result = largest_prime_factor(input);
    std::cout << result << std::endl;
  } catch (const std::invalid_argument& e) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

auto largest_prime_factor(uint64_t n) -> uint64_t {
  const auto factors = prime_factors(n);
  return *std::max_element(factors.begin(), factors.end());
}

auto prime_factors(uint64_t n) -> std::vector<uint64_t> {
  std::vector<uint64_t> out{};
  for (uint64_t i = 2; i <= n; ++i) {
    if (n % i == 0) {
      out.push_back(i);
      n /= i;
    }
  }
  return out;
}
