# Parallel-Programming-Benchmarking-Matrix-Multiplication-Merge-Sort

## Assignment Overview

This assignment focuses on compiling, executing, and benchmarking different parallel programming paradigms—**Sequential**, **Pthreads**, **OpenMP**, and **MPI**—applied to both **matrix multiplication** and **merge sort** algorithms. The goal is to analyze and compare the performance and scalability of these implementations across various problem sizes, ranging from small (5x4, 10x10) to very large matrices (2000x2000, 5000x5000) and array sizes (5 to 5000 elements).[file:1]


## Parallel Programming Models

This project implements four distinct parallelization approaches:

- **Sequential**: Single-threaded baseline implementation for performance comparison
- **Pthreads**: Low-level POSIX threading with fine-grained control over thread management and synchronization
- **OpenMP**: High-level shared-memory parallelism using compiler directives and automatic thread management
- **MPI**: Message-passing interface for distributed-memory parallel computing across multiple processes[file:1]

## Project Structure

'''
.
├── matrix_multiplication/
│ ├── bin/
│ │ ├── seq
│ │ ├── omp
│ │ ├── thread2
│ │ └── mpi
│ ├── data/
│ │ ├── mat_5x4.txt
│ │ ├── mat_4x5.txt
│ │ ├── mat_10x10a.txt
│ │ ├── mat_10x10b.txt
│ │ ├── mat_500x500a.txt
│ │ ├── mat_500x500b.txt
│ │ ├── mat_2000x2000a.txt
│ │ ├── mat_2000x2000b.txt
│ │ └── mat_5000x5000*.txt
│ ├── src/
│ │ ├── matrix.c
│ │ ├── matrix.h
│ │ ├── sequential.c
│ │ ├── omp.c
│ │ ├── thread.c
│ │ ├── thread2.c
│ │ └── mpi.c
│ ├── Makefile
│ ├── randomfloatmatrix.py
│ └── Test-Script.sh
├── mergesort/
│ ├── bin/
│ │ ├── seq
│ │ ├── omp
│ │ ├── pthread
│ │ └── mpi
│ ├── data/
│ │ ├── array_5.txt
│ │ ├── array_10.txt
│ │ ├── array_500.txt
│ │ ├── array_2000.txt
│ │ └── array_5000.txt
│ ├── src/
│ │ ├── mergesort.c
│ │ ├── mergesort.h
│ │ ├── seqmergesort.c
│ │ ├── ompmergesort.c
│ │ ├── pthreadmergesort.c
│ │ └── mpimergesort.c
│ ├── Makefile
│ ├── randomarray.py
│ └── testscript.sh
└── README.md
'''

## Key Components
**Makefile**: Automates compilation of all four implementations with optimized flags (-O2, -fopenmp, -pthread) and organizes executables into the bin/ directory. Simply run make to build all versions.

**Test Script (Test-Script.sh)**: Handles the entire benchmarking workflow automatically:
- Generates test matrices/arrays using Python scripts
- Compiles all programs using the Makefile
- Executes each implementation across different problem sizes
- Measures and records execution times for performance comparison

## Building the Project

'''
Clone the repository
git clone <https://github.com/mperlet/matrix_multiplication.git >
cd assignment4

Run the test script (generates data, compiles, and benchmarks)
chmod +x Test-Script.sh
./Test-Script.sh
'''

## Insights Gained:
**Matrix Multiplication Findings:**

- Sequential: Baseline performance, becomes impractical for large matrices (34+ minutes for 5000x5000)

- OpenMP: Good performance improvement (19 minutes for 5000x5000) with easy implementation

- Pthreads: Better than OpenMP for large matrices (14 minutes for 5000x5000) due to finer control

- MPI: Exceptional performance for large datasets (0.2 seconds for 5000x5000) when distributed across processes

**Merge Sort Findings:**

- Sequential: Most efficient for small to medium datasets due to zero parallel overhead

- OpenMP: Suffers from synchronization overhead in recursive algorithms

- Pthreads: Balanced performance with good control over thread management

- MPI: High communication overhead dominates for small datasets but scales well for larger problems

## References

- M. Perlet, *Matrix Multiplication Benchmark Repository*. GitHub. https://github.com/mperlet/matrix_multiplication


