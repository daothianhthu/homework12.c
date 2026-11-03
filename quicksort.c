#include <stdlib.h>

#define MAX_SIZE 20000

/* Arrays are defined in main.c. */
extern int stackArr[2 * MAX_SIZE + 2];

/* Exchange the values stored at two addresses. */
static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Lomuto partition. Counts comparisons between array values and pivot. */
static int partition(int arr[], int low, int high,
                     int pivotIndex, long long *comparisons)
{
    swap(&arr[pivotIndex], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        (*comparisons)++;

        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

/* Public wrapper so the iterative implementation uses the same partition. */
int partitionForBonus(int arr[], int low, int high,
                      int pivotIndex, long long *comparisons)
{
    return partition(arr, low, high, pivotIndex, comparisons);
}

/* First element of the current subarray. */
static int firstPivot(int low)
{
    return low;
}

/* Choose a new random pivot index in the current subarray. */
static int randomPivot(int low, int high)
{
    return low + rand() % (high - low + 1);
}

/* Return the index of the median among first, middle, and last values. */
int medianOfThree(int arr[], int low, int high,
                  long long *comparisons)
{
    int mid = low + (high - low) / 2;

    int a = arr[low];
    int b = arr[mid];
    int c = arr[high];

    (*comparisons)++;
    if (a < b)
    {
        (*comparisons)++;
        if (b < c)
            return mid;

        (*comparisons)++;
        if (a < c)
            return high;

        return low;
    }
    else
    {
        (*comparisons)++;
        if (a < c)
            return low;

        (*comparisons)++;
        if (b < c)
            return high;

        return mid;
    }
}

void quickSortFirst(int arr[], int low, int high,
                    long long *comparisons)
{
    if (low < high)
    {
        int pivotIndex = firstPivot(low);
        int p = partition(arr, low, high, pivotIndex, comparisons);

        quickSortFirst(arr, low, p - 1, comparisons);
        quickSortFirst(arr, p + 1, high, comparisons);
    }
}

void quickSortRandom(int arr[], int low, int high,
                     long long *comparisons)
{
    if (low < high)
    {
        int pivotIndex = randomPivot(low, high);
        int p = partition(arr, low, high, pivotIndex, comparisons);

        quickSortRandom(arr, low, p - 1, comparisons);
        quickSortRandom(arr, p + 1, high, comparisons);
    }
}

void quickSortMedian(int arr[], int low, int high,
                     long long *comparisons)
{
    if (low < high)
    {
        int pivotIndex = medianOfThree(arr, low, high, comparisons);
        int p = partition(arr, low, high, pivotIndex, comparisons);

        quickSortMedian(arr, low, p - 1, comparisons);
        quickSortMedian(arr, p + 1, high, comparisons);
    }
}
