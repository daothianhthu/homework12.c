#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 20000

/* Arrays are defined in main.c. */
extern int original[MAX_SIZE];
extern int first[MAX_SIZE];
extern int median[MAX_SIZE];

/* Functions implemented in data.c and quicksort.c. */
void generateData(int arr[], int n);
int isSorted(int arr[], int n);
void quickSortMedian(int arr[], int low, int high,
                     long long *comparisons);
void quickSortIterative(int arr[], int low, int high,
                        long long *comparisons);

/* Explicit stack used by Iterative Quick Sort. */
int stackArr[2 * MAX_SIZE + 2];

/* Return elapsed time in milliseconds. */
static double nowMs(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000.0 + t.tv_nsec / 1e6;
}

/* Iterative Quick Sort using Median-of-Three and an explicit stack. */
void quickSortIterative(int arr[], int low, int high,
                        long long *comparisons)
{
    int top = -1;

    stackArr[++top] = low;
    stackArr[++top] = high;

    while (top >= 0)
    {
        int h = stackArr[top--];
        int l = stackArr[top--];

        if (l < h)
        {
            extern int medianOfThree(int arr[], int low, int high,
                                     long long *comparisons);
            extern int partitionForBonus(int arr[], int low, int high,
                                         int pivotIndex,
                                         long long *comparisons);

            int pivotIndex = medianOfThree(arr, l, h, comparisons);
            int p = partitionForBonus(arr, l, h, pivotIndex, comparisons);

            stackArr[++top] = l;
            stackArr[++top] = p - 1;

            stackArr[++top] = p + 1;
            stackArr[++top] = h;
        }
    }
}

void bonusTest(void)
{
    int n = 10000;
    int runs = 200;
    double recTotal = 0.0;
    double iterTotal = 0.0;
    long long recComp = 0;
    long long iterComp = 0;

    generateData(original, n);

    for (int r = 0; r < runs; r++)
    {
        /* Copying is outside the timed section. */
        memcpy(first, original, n * sizeof(int));
        recComp = 0;

        double start = nowMs();
        quickSortMedian(first, 0, n - 1, &recComp);
        recTotal += nowMs() - start;

        /* Copying is outside the timed section. */
        memcpy(median, original, n * sizeof(int));
        iterComp = 0;

        start = nowMs();
        quickSortIterative(median, 0, n - 1, &iterComp);
        iterTotal += nowMs() - start;
    }

    if (!(isSorted(first, n) && isSorted(median, n)) ||
        recComp != iterComp)
    {
        printf("ERROR: bonus test failed!\n");
    }
    else
    {
        printf("Bonus sorting check: Correct\n");
        printf("Comparison counts: Equal\n");
    }

    printf("Data Size : %d\n", n);
    printf("Pivot     : Median-of-Three\n");
    printf("Number of runs: %d\n\n", runs);
    printf("Recursive Quick Sort : %.4f ms\n", recTotal / runs);
    printf("Iterative Quick Sort : %.4f ms\n", iterTotal / runs);
}
