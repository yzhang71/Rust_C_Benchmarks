#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void shellSort(int array[], int len)
{
    int i, j, gap;

    for (gap = len / 2; gap > 0; gap = gap / 2)
        for (i = gap; i < len; i++)
            for (j = i - gap; j >= 0 && array[j] > array[j + gap]; j = j - gap)
                swap(&array[j], &array[j + gap]);
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

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        shellSort(numbers, n);

    }
}
