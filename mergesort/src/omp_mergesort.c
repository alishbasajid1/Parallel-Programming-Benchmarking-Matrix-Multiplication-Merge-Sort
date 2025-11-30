#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mergesort.h"

#define MAX_SIZE 1000000

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s input_file\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("File open error");
        return 1;
    }

    int arr[MAX_SIZE];
    int n = 0;

    while (fscanf(fp, "%d", &arr[n]) == 1 && n < MAX_SIZE) {
        n++;
    }
    fclose(fp);

    int i, width;

    // Bottom-up iterative mergesort with OpenMP parallelization
    for (width = 1; width < n; width *= 2) {
        #pragma omp parallel for schedule(dynamic)
        for (i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = (i + 2 * width - 1 < n - 1) ? i + 2 * width - 1 : n - 1;
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }

    // Print first 10 sorted elements as check
    printf("First 10 elements after sorting:\n");
    for (i = 0; i < 10 && i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

