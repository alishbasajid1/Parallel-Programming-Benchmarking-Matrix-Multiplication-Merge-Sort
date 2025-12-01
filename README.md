# Parallel-Programming-Benchmarking-Matrix-Multiplication-Merge-Sort

This repository contains implementations and performance benchmarks for matrix multiplication and merge sort using four programming paradigms:
- Sequential
- Pthreads
- OpenMP
- MPI

The project compares execution times across varying input sizes (from small 5x4 matrices to large 5000x5000 matrices, and arrays of 5 to 5000 elements) to analyze scalability and parallel overhead.

# Key Features:

Automated compilation and execution via Makefile and Bash scripts

Python scripts for generating test matrices and arrays

Benchmarking across all four implementations for both algorithms

Detailed performance analysis and comparison

# Build & Execution Automation:
- **Makefile**: Automates compilation of all four implementations with optimized flags (-O2, -fopenmp, -pthread) and organizes executables into the bin/ directory. Simply run make to build all versions.

**Test Script (Test-Script.sh)**: Handles the entire benchmarking workflow automatically:
- Generates test matrices/arrays using Python scripts
- Compiles all programs using the Makefile
- Executes each implementation across different problem sizes
- Measures and records execution times for performance comparison

📁 Repository Structure:
text
matrix_multiplication/
├── src/                 # Source files for each implementation
├── bin/                 # Compiled executables
├── data/                # Input matrices and arrays
├── scripts/             # Test and timing scripts
└── Makefile             # Build automation
📈 Insights Gained:
Parallel models (especially MPI) excel with large datasets

Sequential execution is optimal for small workloads

Overhead from threading and communication impacts performance at smaller scales

This project demonstrates hands-on experience with parallel programming, performance evaluation, and automation in a Linux environment.
