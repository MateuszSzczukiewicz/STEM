#include "combinatorics.hpp"
#include "gtest/gtest.h"

using Stats::Combinatorics::combinations;
using Stats::Combinatorics::combinations_with_rep;
using Stats::Combinatorics::factorial;
using Stats::Combinatorics::permutations;
using Stats::Combinatorics::permutations_with_rep;
using Stats::Combinatorics::variations_no_rep;
using Stats::Combinatorics::variations_with_rep;

TEST(CombinatoricsFactorial, BaseCases) {
  EXPECT_EQ(factorial(0), 1);
  EXPECT_EQ(factorial(1), 1);
}

TEST(CombinatoricsFactorial, StandardCases) {
  EXPECT_EQ(factorial(5), 120);
  EXPECT_EQ(factorial(10), 3628800);
}

TEST(CombinatoricsFactorial, ErrorHandling) {
  EXPECT_THROW(factorial(-1), std::domain_error);
  EXPECT_THROW(factorial(21), std::overflow_error);
}

TEST(CombinatoricsPermutations, StandardCases) {
  EXPECT_EQ(permutations(5), 120);
  EXPECT_EQ(permutations(0), 1);
}

TEST(CombinatoricsVariationsRep, StandardCases) {
  EXPECT_EQ(variations_with_rep(10, 3), 1000);  // 10^3
  EXPECT_EQ(variations_with_rep(2, 5), 32);     // 2^5
  EXPECT_EQ(variations_with_rep(5, 0), 1);      // k=0
}

TEST(CombinatoricsVariationsNoRep, StandardCases) {
  EXPECT_EQ(variations_no_rep(5, 3), 60);   // 5 * 4 * 3
  EXPECT_EQ(variations_no_rep(10, 2), 90);  // 10 * 9
}

TEST(CombinatoricsVariationsNoRep, EdgeCases) {
  EXPECT_EQ(variations_no_rep(5, 5), 120);
  EXPECT_EQ(variations_no_rep(5, 0), 1);
  EXPECT_EQ(variations_no_rep(5, 6), 0);  // k > n
}

TEST(CombinatoricsCombinations, BaseCases) {
  EXPECT_EQ(combinations(10, 0), 1);   // (n 0)
  EXPECT_EQ(combinations(10, 10), 1);  // (n n)
  EXPECT_EQ(combinations(10, 1), 10);
}

TEST(CombinatoricsCombinations, StandardCases) {
  EXPECT_EQ(combinations(10, 3), 120);
  EXPECT_EQ(combinations(7, 2), 21);

  EXPECT_EQ(combinations(4, 3), 4);
  EXPECT_EQ(combinations(8, 5), 56);
}

TEST(CombinatoricsCombinations, Symmetry) {
  EXPECT_EQ(combinations(10, 8), combinations(10, 2));
  EXPECT_EQ(combinations(10, 8), 45);
}

TEST(CombinatoricsCombinations, EdgeCases) {
  EXPECT_EQ(combinations(5, 6), 0);   // k > n
  EXPECT_EQ(combinations(5, -1), 0);  // k < 0
}

TEST(CombinatoricsCombinationsRep, StandardCases) {
  // C'(n, k) = C(n+k-1, k)
  // C'(3, 2) = C(3+2-1, 2) = C(4, 2) = 6
  EXPECT_EQ(combinations_with_rep(3, 2), 6);
  // C'(2, 3) = C(2+3-1, 3) = C(4, 3) = 4
  EXPECT_EQ(combinations_with_rep(2, 3), 4);
}

TEST(CombinatoricsPermutationsRep, StandardCases) {
  // AABC (n=4, k_A=2, k_B=1, k_C=1)
  // 4! / (2! * 1! * 1!) = 24 / 2 = 12
  std::vector<int> counts_AABC = {2, 1, 1};
  EXPECT_EQ(permutations_with_rep(counts_AABC), 12);

  // (n=10, M=2, A=3, T=2, E=1, Y=1, K=1)
  std::vector<int> counts_MATH = {2, 3, 2, 1, 1, 1};
  // 10! / (2! * 3! * 2! * 1! * 1! * 1!) = 3628800 / (2 * 6 * 2) = 151200
  EXPECT_EQ(permutations_with_rep(counts_MATH), 151200);
}
