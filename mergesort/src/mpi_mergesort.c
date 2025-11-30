#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "mergesort.h"

#define MAX_SIZE 1000000

// Simple helper to merge two sorted arrays into result
void mergeArrays(int *leftArr, int leftSize, int *rightArr, int rightSize, int *result) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            result[k++] = leftArr[i++];
        } else {
            result[k++] = rightArr[j++];
        }
    }
    while (i < leftSize) result[k++] = leftArr[i++];
    while (j < rightSize) result[k++] = rightArr[j++];
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr = NULL;
    int n = 0;

    if (rank == 0) {
        if (argc != 2) {
            printf("Usage: %s input_file\n", argv[0]);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            perror("File open error");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Read input into temporary array first to get size
        int temp_arr[MAX_SIZE];
        n = 0;
        while (fscanf(fp, "%d", &temp_arr[n]) == 1 && n < MAX_SIZE) {
            n++;
        }
        fclose(fp);

        arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            arr[i] = temp_arr[i];
        }
    }

    // Broadcast size to all
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate portion size for each process
    int chunk_size = n / size;
    int remainder = n % size;

    int start = rank * chunk_size + (rank < remainder ? rank : remainder);
    int end = start + chunk_size - 1;
    if (rank < remainder) {
        end++;
    }

    int local_n = end - start + 1;
    int *local_arr = (int *)malloc(local_n * sizeof(int));

    // Scatter data to each process
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            int s = i * chunk_size + (i < remainder ? i : remainder);
            int e = s + chunk_size - 1;
            if (i < remainder) {
                e++;
            }
            int len = e - s + 1;

            if (i == 0) {
                for (int j = 0; j < len; j++) {
                    local_arr[j] = arr[j];
                }
            } else {
                MPI_Send(arr + s, len, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        MPI_Recv(local_arr, local_n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Each process sorts its part
    mergeSort(local_arr, 0, local_n - 1);

    // Now perform tree-based merge from bottom up
    int step = 1;
    while (step < size) {
        if (rank % (2 * step) == 0) {
            int from = rank + step;
            if (from < size) {
                int recv_n;
                MPI_Recv(&recv_n, 1, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                int *recv_arr = (int *)malloc(recv_n * sizeof(int));
                MPI_Recv(recv_arr, recv_n, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                int *merged_arr = (int *)malloc((local_n + recv_n) * sizeof(int));
                mergeArrays(local_arr, local_n, recv_arr, recv_n, merged_arr);

                free(local_arr);
                free(recv_arr);

                local_arr = merged_arr;
                local_n += recv_n;
            }
        } else {
            int to = rank - step;
            MPI_Send(&local_n, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
            MPI_Send(local_arr, local_n, MPI_INT, to, 0, MPI_COMM_WORLD);
            break;
        }
        step *= 2;
    }

    if (rank == 0) {
        // Print first 10 sorted elements as check
        printf("First 10 elements after sorting:\n");
        for (int i = 0; i < 10 && i < local_n; i++) {
            printf("%d ", local_arr[i]);
        }
        printf("\n");
        free(arr);
        free(local_arr);
    } else {
        free(local_arr);
    }

    MPI_Finalize();
    return 0;
}

