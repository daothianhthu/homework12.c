#include <stdlib.h>

/* Generate random integer data in the range 0 to 99,999. */
void generateData(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100000;
    }
}

/* Return 1 if the array is sorted in ascending order; otherwise return 0. */
int isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            return 0;
        }
    }

    return 1;
}