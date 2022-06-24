/**
 * @file
 * @brief Program to perform [binary
 * search](https://en.wikipedia.org/wiki/Binary_search_algorithm) of a target
 * value in a given *sorted* array.
 * @authors [James McDermott](https://github.com/theycallmemac) - recursive
 * algorithm
 * @authors [Krishna Vedala](https://github.com/kvedala) - iterative algorithm
 */
#include <assert.h>     /// for assert
#include <stdbool.h>    /// for bool
#include <stdio.h>      /// for IO operations
#include <stdlib.h>     /// for dynammic memory allocation

/** Iterative implementation
 * \param[in] arr array to search
 * \param l left index of search range
 * \param r right index of search range
 * \param x target value to search for
 * \returns location of x assuming array arr[l..r] is present
 * \returns -1 otherwise
 */
int binarysearch2(const int *arr, int l, int r, int x, int *k)
{
    int mid = l + (r - l) / 2;

    while (arr[mid] != x)
    {
        if (r <= l || r < 0)
            return -1;

        if (arr[mid] > x)
            // If element is smaller than middle
            r = mid - 1;
        else
            // Else element is in right subarray
            l = mid + 1;

        mid = l + (r - l) / 2;
    }

    // When element is not present in array
    *k = mid;
    return mid;
}

int n = 97;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    int *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%d", &numbers[i]);
    }

    int k = 0;

    for (int i = 0; i < 300000000; i++)

    {
        int z = 0;

        k = k + binarysearch2(numbers, 0, n, 284, &z);

    }
    return k;
}
