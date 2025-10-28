#include <cstdint>
#include <exception>
#include <iostream>
#include <print>

#include "combinatorics.hpp"

int main() {
  try {
    constexpr int white_balls = 3;
    constexpr int blue_balls = 7;
    constexpr int total_balls = white_balls + blue_balls;
    constexpr int drawn_balls = 3;

    constexpr int64_t omega =
        Stats::Combinatorics::combinations(total_balls, drawn_balls);

    constexpr int64_t first_case =
        Stats::Combinatorics::combinations(blue_balls, 2) *
        Stats::Combinatorics::combinations(white_balls, 1);
    constexpr int64_t second_case =
        Stats::Combinatorics::combinations(blue_balls, 3) *
        Stats::Combinatorics::combinations(white_balls, 0);

    constexpr int64_t favorable = first_case + second_case;

    double probability = static_cast<double>(favorable) / omega;

    std::print("{:.10f}\n", probability);
  } catch (const std::exception& e) {
    std::cerr << "Calculation error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
