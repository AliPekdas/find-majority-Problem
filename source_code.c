#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000
#define MAX_LINE 10000

// Utility Functions
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++){ 
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void copyArray(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++){
        dest[i] = src[i];
    }
}

int countFrequency(int A[], int n, int key) {
    int count = 0;
    for (int i = 0; i < n; i++){ 
        if (A[i] == key) 
            count++;
    }
    return count;
}

void printResult(const char* method, int result, double time) {
    printf("[%s] Majority: %d, Time: %.3f μs\n", method, result, time);
}

double time_diff_sec(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;  // microsecond(μs)
}

// Brute Force
int Brute_Force(int arr[], int size){
    for(int i = 0; i < size; i++){
        int k = 0;
        for(int j = 0; j < size; j++){
            if(arr[i] == arr[j])
                k++;
        }
        if(k > size / 2)
            return arr[i];
    }
    return -1;
}

// Insertion Sort
void Insertion_Sort(int arr[], int size){
    for(int i = 1; i < size; i++){
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && key < arr[j]){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int findMajorityInsertionSort(int A[], int n) {
    Insertion_Sort(A, n);
    int candidate = A[n / 2];
    int count = countFrequency(A, n, candidate);
    return (count > n / 2) ? candidate : -1;
}

// Merge Sort
void merge(int arr[], int left, int mid, int right){
    int LS = mid - left + 1;
    int RS = right - mid;
    int leftArr[LS], rightArr[RS];

    for(int i = 0; i < LS; i++)
        leftArr[i] = arr[left + i];
    for(int j = 0; j < RS; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while(i < LS && j < RS){
        if(leftArr[i] < rightArr[j]){
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while(i < LS)
        arr[k++] = leftArr[i++];
    while(j < RS)
        arr[k++] = rightArr[j++];
}

void Merge_Sort(int arr[], int left, int right) {
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    Merge_Sort(arr, left, mid);
    Merge_Sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int findMajorityMergeSort(int A[], int n) {
    Merge_Sort(A, 0, n - 1);
    int candidate = A[n / 2];
    int count = countFrequency(A, n, candidate);
    return (count > n / 2) ? candidate : -1;
}

// Quick Sort
void Quick_Sort(int A[], int low, int high) {
    if (low < high) {
        int pivot = A[low];
        int i = low + 1, j = high;
        while (i <= j) {
            while (i <= j && A[i] <= pivot) i++;
            while (i <= j && A[j] > pivot) j--;
            if (i < j) {
                int t = A[i]; A[i] = A[j]; A[j] = t;
            }
        }
        int t = A[low]; A[low] = A[j]; A[j] = t;
        Quick_Sort(A, low, j - 1);
        Quick_Sort(A, j + 1, high);
    }
}

int findMajorityQuickSort(int A[], int n) {
    Quick_Sort(A, 0, n - 1);
    int candidate = A[n / 2];
    int count = countFrequency(A, n, candidate);
    return (count > n / 2) ? candidate : -1;
}

// Divide and Conquer
int Divide_and_Conquer(int A[], int l, int r) {
    if (l == r) return A[l];
    int mid = (l + r) / 2;
    int left = Divide_and_Conquer(A, l, mid);
    int right = Divide_and_Conquer(A, mid + 1, r);
    if (left == right) return left;
    int leftCount = countFrequency(A + l, r - l + 1, left);
    int rightCount = countFrequency(A + l, r - l + 1, right);
    return (leftCount > (r - l + 1) / 2) ? left : (rightCount > (r - l + 1) / 2) ? right : -1;
}

int findMajorityDivideandConquer(int A[], int n) {
    return Divide_and_Conquer(A, 0, n - 1);
}

// Hashing
int Hashing(int A[], int n) {
    int freq[MAX] = {0};
    for (int i = 0; i < n; i++) {
        freq[A[i]]++;
        if (freq[A[i]] > n / 2) return A[i];
    }
    return -1;
}

// Boyer-Moore Voting
int Boyer_Moore(int arr[], int size){
    int candidate = arr[0], count = 1;
    for(int i = 1; i < size; i++){
        if(arr[i] == candidate)
            count++;
        else if(--count == 0){
            candidate = arr[i];
            count = 1;
        }
    }
    count = 0;
    for(int i = 0; i < size; i++)
        if(arr[i] == candidate) count++;
    return (count > size / 2) ? candidate : -1;
}

// Pairwise Comparison
int Pairwise_Comparison(int A[], int n) {
    if (n == 0) return -1;
    int first = A[0], second = -1, fCount = 1, sCount = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] == first) fCount++;
        else if (A[i] == second) sCount++;
        else if (fCount == 0) { first = A[i]; fCount = 1; }
        else if (sCount == 0) { second = A[i]; sCount = 1; }
        else { fCount--; sCount--; }
    }
    fCount = sCount = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] == first) fCount++;
        if (A[i] == second) sCount++;
    }
    if (fCount > n / 2) return first;
    if (sCount > n / 2) return second;
    return -1;
}

int parseLine(char *line, int A[]) {
    int count = 0;
    char *token = strtok(line, ", \n");
    while (token != NULL) {
        A[count++] = atoi(token);
        token = strtok(NULL, ", \n");
    }
    return count;
}

// Main Function
int main() {
    FILE *fptr = fopen("inputs.txt", "r");
    if (!fptr) {
        printf("Failed to open inputs.txt\n");
        return 1;
    }

    char line[MAX_LINE];
    int A[MAX], B[MAX];

    struct {
        const char *name;
        int (*func)(int[], int);
    } algorithms[] = {
        {"BruteForce", Brute_Force},
        {"InsertionSort", findMajorityInsertionSort},
        {"MergeSort", findMajorityMergeSort},
        {"QuickSort", findMajorityQuickSort},
        {"DivideConquer", findMajorityDivideandConquer},
        {"Hashing", Hashing},
        {"BoyerMoore", Boyer_Moore},
        {"PairwiseComparison", Pairwise_Comparison}
    };

    int inputCount = 1;
    while (fgets(line, sizeof(line), fptr)) {
        int n = parseLine(line, A);
        printf("\nInput %d (%d elements):\n", inputCount++, n);
        printArray(A, n);

        for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); i++) {
            copyArray(B, A, n);

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);
            int r = algorithms[i].func(B, n);
            clock_gettime(CLOCK_MONOTONIC, &end);

            double duration = time_diff_sec(start, end);
            printResult(algorithms[i].name, r, duration);
        }
    }

    fclose(fptr);
    return 0;
}