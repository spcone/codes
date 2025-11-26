#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 100

int array[SIZE];
int temp[SIZE];

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (array[i] < array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }
    while (i <= mid) temp[k++] = array[i++];
    while (j <= right) temp[k++] = array[j++];

    for (i = left; i <= right; i++) {
        array[i] = temp[i];
    }
}

void merge_sort_range(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort_range(left, mid);
        merge_sort_range(mid + 1, right);
        merge(left, mid, right);
    }
}

void* merge_sort(void* arg) {
    int left = *(int*)arg;
    int right = left + (SIZE / 4) - 1;
    merge_sort_range(left, right);
    return NULL;
}

int main() {
    pthread_t threads[4];
    int thread_ids[4];

    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }

    for (int i = 0; i < 4; i++) {
        thread_ids[i] = i * (SIZE / 4);
        pthread_create(&threads[i], NULL, merge_sort, &thread_ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    int quarter = SIZE / 4;

    merge(0, quarter - 1, 2 * quarter - 1);
    merge(2 * quarter, 3 * quarter - 1, SIZE - 1);
    merge(0, 2 * quarter - 1, SIZE - 1);

    printf("Sorted Array \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

