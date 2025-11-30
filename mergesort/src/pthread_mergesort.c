#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mergesort.h"

#define MAX_SIZE 1000000
#define THREADS 4

typedef struct {
    int *arr;
    int left;
    int right;
} thread_data_t;

void *threaded_mergeSort(void *arg);

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

    pthread_t threads[THREADS];
    thread_data_t thread_data[THREADS];

    int segment_size = n / THREADS;
    for (int i = 0; i < THREADS; i++) {
        thread_data[i].arr = arr;
        thread_data[i].left = i * segment_size;
        thread_data[i].right = (i == THREADS - 1) ? n - 1 : (thread_data[i].left + segment_size - 1);

        pthread_create(&threads[i], NULL, threaded_mergeSort, &thread_data[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge the sorted segments
    int current_size = segment_size;
    while (current_size < n) {
        int left = 0;
        while (left + current_size < n) {
            int mid = left + current_size - 1;
            int right = (left + 2 * current_size - 1 < n) ? left + 2 * current_size - 1 : n - 1;
            merge(arr, left, mid, right);
            left += 2 * current_size;
        }
        current_size *= 2;
    }

    // Print first 10 sorted elements as check
    printf("First 10 elements after sorting:\n");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void *threaded_mergeSort(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    mergeSort(data->arr, data->left, data->right);
    return NULL;
}

