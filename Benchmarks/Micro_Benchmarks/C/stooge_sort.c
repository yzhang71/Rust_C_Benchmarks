#include <stdio.h>
#include <stdlib.h>

void stoogesort(int arr[], int i, int j)
{
    int temp, k;
    if (arr[i] > arr[j])
    {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    if ((i + 1) >= j)
        return;
    k = (int)((j - i + 1) / 3);
    stoogesort(arr, i, j - k);
    stoogesort(arr, i + k, j);
    stoogesort(arr, i, j - k);
}

int n = 97;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    int *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%d", &numbers[i]);
    }

    int size = 10000;

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        stoogesort(numbers, 0, n - 1);

    }
}
