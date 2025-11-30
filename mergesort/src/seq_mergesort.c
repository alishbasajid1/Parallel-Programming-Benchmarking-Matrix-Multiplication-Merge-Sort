#include <stdio.h>
#include <stdlib.h>
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

    mergeSort(arr, 0, n - 1);

    // Print first 10 sorted elements as check
    printf("First 10 elements after sorting:\n");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

