#include <stdlib.h>

#include "sort.h"

static void merge_swap(int arr[], const int left, const int mid, const int right, int tmp[]) {
    int i = left;
    int j = mid + 1;
    int t = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            tmp[t] = arr[i];
            t++;
            i++;
        }
        else {
            tmp[t] = arr[j];
            t++;
            j++;
        }
    }
    while (i <= mid) {
        tmp[t] = arr[i];
        t++;
        i++;
    }
    while (j <= right) {
        tmp[t] = arr[j];
        t++;
        j++;
    }
    t = 0;
    int temp_left = left;
    while (temp_left <= right) {
        arr[temp_left] = tmp[t];
        t++;
        temp_left++;
    }
}

static void do_merge(int arr[], const int left, const int right, int tmp[]) {
    if (left < right) {
        const int mid = (left + right) / 2;
        do_merge(arr, left, mid, tmp);
        do_merge(arr, mid + 1, right, tmp);
        merge_swap(arr, left, mid, right, tmp);
    }
}

static void quick(int arr[], const int left, const int right) {
    int l = left;
    int r = right;
    const int pivot = arr[(left + right) / 2];
    int elem;
    while (l < r) {
        while (arr[l] < pivot)
            l++;
        while (arr[r] > pivot)
            r--;
        if (l >= r)
            break;

        elem = arr[l];
        arr[l] = arr[r];
        arr[r] = elem;
        if (arr[l] == pivot)
            r--;
        if (arr[r] == pivot)
            l++;
    }
    if (l == r) {
        l++;
        r--;
    }
    if (left < r)
        quick(arr, left, r);
    if (right > l)
        quick(arr, l, right);
}

void sort_bubble(const int length, int arr[]) {
    _Bool flag = 1;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                arr[j] = arr[j] + arr[j + 1];
                arr[j + 1] = arr[j] - arr[j + 1];
                arr[j] = arr[j] - arr[j + 1];
                flag = 0;
            }
        }
        if (flag) break;
        flag = 1;
    }
}

void sort_select(const int length, int arr[]) {
    for (int i = 0; i < length; i++) {
        int min = arr[i];
        int index = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < min) {
                min = arr[j];
                index = j;
            }
        }
        if (index != i) {
            arr[i] = arr[index] + arr[i];
            arr[index] = arr[i] - arr[index];
            arr[i] = arr[i] - arr[index];
        }
    }
}

void sort_insert(const int length, int arr[]) {
    for (int i = 1; i < length; i++) {
        const int elem = arr[i];
        int index = i - 1;
        while (index >= 0 && arr[index] > elem) {
            arr[index + 1] = arr[index];
            index--;
        }
        arr[index + 1] = elem;
    }
}

void sort_shell(const int length, int arr[]) {
    for (int gap = length / 2; gap > 0; gap = gap / 2) {
        for (int i = gap; i < length; i++) {
            int index = i;
            const int elem = arr[i];
            while (index - gap >= 0 && elem < arr[index - gap]) {
                arr[index] = arr[index - gap];
                index -= gap;
            }
            arr[index] = elem;
        }
    }
}

void sort_quick(const int length, int arr[]) {
    quick(arr, 0, length - 1);
}

void sort_merge(const int length, int arr[]) {
    int* tmp = calloc(length, sizeof(int));
    do_merge(arr, 0, length - 1, tmp);
}

void sort_radix(const int length, int arr[]) {
    int max = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    int digit = 1;
    for (int n = 10; max > n; n *= 10)
        digit++;

    int bucket[10][length];
    int bucketCount[10];
    for (int i = 0, n = 1; i < digit; i++, n *= 10) {
        for (int j = 0; j < length; j++) {
            const int digitOfElem = arr[j] / n % 10;
            bucket[digitOfElem][bucketCount[digitOfElem]] = arr[j];
            bucketCount[digitOfElem]++;
        }
        int index = 0;
        for (int k = 0; k < 10; k++) {
            if (bucketCount[k] != 0) {
                for (int l = 0; l < bucketCount[k]; l++) {
                    arr[index] = bucket[k][l];
                    index++;
                }
            }
            bucketCount[k] = 0;
        }
    }
}
