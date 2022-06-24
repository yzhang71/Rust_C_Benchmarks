// A Dynamic Programming solution for Rod cutting problem
#include<limits.h>
#include <string.h>
#include <assert.h>     /// for assert
#include <stdbool.h>    /// for bool
#include <stdio.h>      /// for IO operations
#include <stdlib.h>     /// for dynammic memory allocation

// A utility function to get the maximum of two integers
int max(int a, int b) { return (a > b)? a : b;}

/* Returns the best obtainable price for a rod of length n and
price[] as prices of different pieces */
int cutRod(int price[], int n, int* k)
{
    int val[n+1];
    val[0] = 0;
    int i, j;

    // Build the table val[] in bottom up manner and return the last entry
    // from the table
    for (i = 1; i<=n; i++)
    {
        int max_val = INT_MIN;
        for (j = 0; j < i; j++)
            max_val = max(max_val, price[j] + val[i-j-1]);
        val[i] = max_val;
    }
    *k = val[n];

    return val[n];
}

int n = 97;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    int *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%d", &numbers[i]);
    }

    int size = 3000000;

    int k = 0;

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        k = k + cutRod(numbers, n, &k);

    }

    return k;
}

