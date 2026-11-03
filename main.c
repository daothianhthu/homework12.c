#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 20000

int original[MAX_SIZE];
int first[MAX_SIZE];
int randomArr[MAX_SIZE];
int median[MAX_SIZE];

int sizes[] = {1000, 2000, 4000, 8000, 16000, 20000};

/* Functions implemented in data.c */
void generateData(int arr[], int n);
int isSorted(int arr[], int n);

/* Functions implemented in quicksort.c */
void quickSortFirst(int arr[], int low, int high,
                    long long *comparisons);
void quickSortRandom(int arr[], int low, int high,
                     long long *comparisons);
void quickSortMedian(int arr[], int low, int high,
                     long long *comparisons);

/* Function implemented in bonus.c */
void bonusTest(void);

int main(void)
{
    srand((unsigned int)time(NULL));

    for (int k = 0; k < 6; k++)
    {
        int n = sizes[k];

        generateData(original, n);

        memcpy(first, original, n * sizeof(int));
        memcpy(randomArr, original, n * sizeof(int));
        memcpy(median, original, n * sizeof(int));

        long long firstComparisons = 0;
        long long randomComparisons = 0;
        long long medianComparisons = 0;

        quickSortFirst(first, 0, n - 1, &firstComparisons);
        quickSortRandom(randomArr, 0, n - 1, &randomComparisons);
        quickSortMedian(median, 0, n - 1, &medianComparisons);

        printf("Data Size : %d\n\n", n);
        printf("Quick Sort (First)    : %lld comparisons\n",
               firstComparisons);
        printf("Quick Sort (Random)   : %lld comparisons\n",
               randomComparisons);
        printf("Quick Sort (Median-3) : %lld comparisons\n",
               medianComparisons);

        if (isSorted(first, n) &&
            isSorted(randomArr, n) &&
            isSorted(median, n))
        {
            printf("Sorting result: Correct\n");
        }
        else
        {
            printf("ERROR: sorting failed!\n");
        }

        printf("\n");
    }

    bonusTest();

    return 0;
}
