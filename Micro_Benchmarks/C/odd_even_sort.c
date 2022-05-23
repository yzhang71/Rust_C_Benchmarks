/**
 * @file
 * @author [Edwin Ajong](https://github.com/eddybruv)
 * @brief [Odd Even Sort](https://en.wikipedia.org/wiki/Odd%E2%80%93even_sort) implementation
 * @details
 * This algorithm is divided into two phases- Odd and Even Phase.
 * The algorithm runs until the array elements are sorted and in each iteration two phases occurs- Odd and Even Phases.
 * In the odd phase, we perform a bubble sort on odd indexed elements and in the even phase,
 * we perform a bubble sort on even indexed elements.
 * Time Complexity: O(N ^ 2)
 */

#include <assert.h>     /// for assert
#include <stdbool.h>    /// for bool
#include <stdio.h>      /// for IO operations
#include <stdlib.h>     /// for dynammic memory allocation
#include <time.h>       /// for random number generation
#include <inttypes.h>   /// for int32_t types

/**
 * @brief Swap numbers by reference(using pointers)
 * @param first pointer to first number
 * @param second pointer to second number
 * @returns void
 */
void swap(int32_t *first, int32_t *second)
{
    int32_t temp = *first;
    *first = *second;
    *second = temp;
}

/**
 * @brief oddEvenSort sorts the array using the algorithm described above.
 * @details 
 * A boolean varaible(isSorted) is declared and initialised to "false".
 * In the while loop, the variable(isSorted) is then set to "true".
 * During even phase the for loop loops through the array, touching just the even indexes.
 * i.e arr[0], arr[2], arr[4] and so on.
 * While during the odd phase, the for loop loops through the array, touching just the odd indexes.
 * i.e arr[1], arr[3], arr[5] and so on.
 * During these phases, if the if statement check if the interger at the current position in the array
 * is greater than the interger at the next array index (i.e arr[index + 2], to make sure the index is odd
 * during the odd phase and even during the even phase).
 * If the condition is true, the function "swap" is called and address of the intergers in question are passed as
 * parameters. After the swap is completed, "isSorted" is set to "false".
 * The while loop will keep running till the array is propertly sorted.
 * @param arr array to be sorted
 * @param size the size of the array
 * @returns void
 */
void oddEvenSort(int *arr, int size)
{

    bool isSorted = false;
    while(!isSorted)
    {
        isSorted = true;
        int32_t i;

        // Even phase
        for(i = 0; i <= size - 2; i += 2)
        {
            if(arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                isSorted = false;
            }
        }

        // Odd phase
        for(i = 1; i <= size - 2; i += 2)
        {
            if(arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                isSorted = false;
            }
        }
    }
}

/**
 * @brief Main function
 */

int n = 1372;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    int *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%d", &numbers[i]);
    }

    int size = 2000000;

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        oddEvenSort(numbers, n);

    }
}

