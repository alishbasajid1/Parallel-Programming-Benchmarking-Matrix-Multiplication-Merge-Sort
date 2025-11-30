CC = gcc
CFLAGS = -Wall -std=gnu99 -g -fopenmp
TUNE = -O2

all: sequential pthread omp mpi

sequential:
	$(CC) $(TUNE) $(CFLAGS) -o bin/seq_mergesort src/seq_mergesort.c src/mergesort.c

pthread:
	$(CC) $(TUNE) $(CFLAGS) -pthread -o bin/pthread_mergesort src/pthread_mergesort.c src/mergesort.c

omp:
	$(CC) $(TUNE) $(CFLAGS) -o bin/omp_mergesort src/omp_mergesort.c src/mergesort.c

mpi:
	mpicc $(TUNE) $(CFLAGS) -o bin/mpi_mergesort src/mpi_mergesort.c src/mergesort.c


