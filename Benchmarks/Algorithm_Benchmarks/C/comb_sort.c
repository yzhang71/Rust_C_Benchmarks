#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
// #define SHRINK 2  // suggested shrink factor value

void sort(int numbers[], int size)
{
    int gap = size;
    float SHRINK = 2.0;
    while (gap > 1)  // gap = 1 means that the array is sorted
    {
        gap = gap / SHRINK;
        int i = 0;
        while ((i + gap) < size)
        {  // similiar to the Shell Sort
            if (numbers[i] > numbers[i + gap])
            {
                int tmp = numbers[i];
                numbers[i] = numbers[i + gap];
                numbers[i + gap] = tmp;
            }
            i++;
        }
    }
}

int n = 97;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    int *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%d", &numbers[i]);
    }

    int size = 10000000;

    double time_spent = 0.0;
 
    clock_t begin = clock();

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        sort(numbers, n);

    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
}
