#include <stdio.h>
#include <stdlib.h>

int fibMonaccianSearch(int arr[], int x, int n)
{
    /* Initialize fibonacci numbers */
    int fibMMm2 = 0;               // (m-2)'th Fibonacci No.
    int fibMMm1 = 1;               // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci

    /* fibM is going to store the smallest Fibonacci
       Number greater than or equal to n */
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    // Marks the eliminated range from front
    int offset = -1;

    /* while there are elements to be inspected. Note that
       we compare arr[fibMm2] with x. When fibM becomes 1,
       fibMm2 becomes 0 */
    while (fibM > 1)
    {
        // Check if fibMm2 is a valid location

        // sets i to the min. of (offset+fibMMm2) and (n-1)
        int i = ((offset + fibMMm2) < (n - 1)) ? (offset + fibMMm2) : (n - 1);

        /* If x is greater than the value at index fibMm2,
           cut the subarray array from offset to i */
        if (arr[i] < x)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }

        /* If x is greater than the value at index fibMm2,
           cut the subarray after i+1  */
        else if (arr[i] > x)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }

        /* element found. return index */
        else
            return i;
    }

    /* comparing the last element with x */
    if (fibMMm1 && arr[offset + 1] == x)
        return offset + 1;

    /*element not found. return -1 */
    return -1;
}

int n = 97;

/** Driver Code */
int main(int argc, const char *argv[]) {

    int size = 200000000;

    int cnt = 0;

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        int arr[] = {371, 323, 241, 181, 90, 102, 11, 198, 20, 121, 441, 57, 225, 218, 284, 425, 223, 213, 158, 366, 637, 180, 520, 386, 641, 128, 77, 492, 71, 86, 279, 401, 476, 414, 444, 317, 39, 238, 375, 499, 236, 163, 546, 242, 402, 603, 614, 83, 541, 25, 72, 234, 140, 639, 248, 544, 96, 27, 66, 581, 273, 133, 190, 320, 721, 221, 361, 391, 145, 752, 472, 3, 447, 219, 161, 237, 718, 157, 184, 147, 247, 604, 587, 583, 405, 58, 346, 433, 172, 460, 62, 265, 92, 351, 122, 120, 114, 245};


        cnt = cnt + fibMonaccianSearch(arr, 245, n);

    }

    return cnt;
}
