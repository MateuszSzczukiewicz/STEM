# Statistics and Probability

This module contains practical implementations and simulations of concepts from statistics and probability, based on my university coursework (including RPiS materials).

The goal is twofold:

1. **Analytical Implementation:** To translate formulas and theories from textbooks (e.g., RPiS No. 1, RPiS No. 2) into reusable C++ libraries.
2. **Simulation & Verification:** To use Monte Carlo simulations to verify these same theories in practice, building a deeper, more intuitive understanding.

## Directory Structure

### `/lib` - Reusable Libraries

Core C++ libraries implementing statistical and probabilistic formulas:

- `/lib/combinatorics` - Permutations, combinations, and variations
- `/lib/distributions` - Probability distributions (Binomial, Normal, etc.)
- `/lib/random_variables` - Random variable analysis (E(X), Var(X))
- `/lib/limit_theorems` - Central limit theorems (Moivre-Laplace)
- `/lib/descriptive_stats` - Descriptive statistics (mean, median, quantiles)
- `/lib/inference` - Statistical inference (confidence intervals, hypothesis testing)

### `/tasks` - Problem Solutions

Each task contains:
- `analytics.cpp` - Analytical solution using `/lib`
- `simulation.cpp` - Monte Carlo verification
- `report.Rmd` - R Markdown report combining both approaches
- `CMakeLists.txt` - Build configuration

Example: `/tasks/combinatorics_urn_sampling`

### `/tests` - Unit Tests

Google Test suites for validating library implementations.

## How to Build

The project uses a Makefile for easy automation:

```bash
# Build all C++ executables
make build

# Run all tests
make test

# Generate report for specific task
make report TASK=combinatorics_urn_sampling

# Generate all reports
make reports

# Install R dependencies (first time only)
make install-r-deps

# Clean build artifacts
make clean

# Show all available commands
make help
```

### Manual CMake build:
```bash
mkdir build
cd build
cmake ..
make
```

### Report Generation
Each task can generate PDF and HTML reports using R Markdown:

```bash
# Using Makefile
make report TASK=combinatorics_urn_sampling

# Using script directly
./scripts/generate_report.sh combinatorics_urn_sampling

# Manual R command
cd tasks/combinatorics_urn_sampling
R -e "rmarkdown::render('report.Rmd')"
```

**First time setup for reports:**
```bash
make install-r-deps
```
