#ifndef LIB_COMBINATORICS_HPP
#define LIB_COMBINATORICS_HPP

#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace Stats::Combinatorics {

constexpr int64_t factorial(int n) {
  if (n < 0) {
    throw std::domain_error("Factorial not defined for negative numbers");
  }
  if (n == 0) {
    return 1;
  };

  int64_t result = 1;
  for (int i = 2; i <= n; ++i) {
    if (__builtin_mul_overflow(result, i, &result)) {
      throw std::overflow_error("Factorial overflow");
    }
  }
  return result;
}

constexpr int64_t permutations(int n) { return factorial(n); }

constexpr int64_t variations_with_rep(int n, int k) {
  if (k < 0 || n < 0) {
    return 0;
  };
  if (k == 0) {
    return 1;
  }
  if (n == 0) {
    return 0;
  }

  int64_t result = 1;
  for (int i = 0; i < k; ++i) {
    if (__builtin_mul_overflow(result, n, &result)) {
      throw std::overflow_error("Variations with repetition overflow");
    }
  }

  return result;
}

constexpr int64_t variations_no_rep(int n, int k) {
  if (k < 0 || n < 0) {
    return 0;
  }
  if (k > n) {
    return 0;
  }

  int64_t result = 1;
  for (int i = 0; i < k; ++i) {
    if (__builtin_mul_overflow(result, (n - i), &result)) {
      throw std::overflow_error("Variations no repetition overflow");
    }
  }
  return result;
}

constexpr int64_t combinations(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  if (k == 0 || k == n) {
    return 1;
  }
  if (k > n / 2) {
    k = n - k;
  }

  int64_t res = 1;
  for (int i = 1; i <= k; ++i) {
    if (res > __LONG_LONG_MAX__ / (n - i + 1)) {
      throw std::overflow_error("Combinations overflow");
    }
    res = res * (n - i + 1) / i;
  }
  return res;
}

constexpr int64_t combinations_with_rep(int n, int k) {
  if (k < 0 || n <= 0) {
    return 0;
  }
  if (k == 0) {
    return 1;
  }
  return combinations(n + k - 1, k);
}

inline int64_t permutations_with_rep(const std::vector<int>& k_counts) {
  int n = std::accumulate(k_counts.begin(), k_counts.end(), 0);

  int64_t denominator = 1;
  for (int k : k_counts) {
    denominator *= factorial(k);
  }

  if (denominator == 0) {
    throw std::runtime_error("Division by zero in permutations_with_rep");
  }
  return factorial(n) / denominator;
}
}  // namespace Stats::Combinatorics

#endif
