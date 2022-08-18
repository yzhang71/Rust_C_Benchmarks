#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int temp;
void stoogesort(int arr[], int l, int h)
{
  
    // If first element is smaller than last,
    // swap them
    if (arr[l] > arr[h]) {
        temp = arr[l];
        arr[l] = arr[h];
        arr[h] = temp;
    }
  
    // If there are more than 2 elements in
    // the array
    if (h - l + 1 > 2) {
        int t = (h - l + 1) / 3;
  
        // Recursively sort first 2/3 elements
        stoogesort(arr, l, h - t);
  
        // Recursively sort last 2/3 elements
        stoogesort(arr, l + t, h);
  
        // Recursively sort first 2/3 elements
        // again to confirm
        stoogesort(arr, l, h - t);
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

    int size = 10000;

    double time_spent = 0.0;
 
    clock_t begin = clock();

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        stoogesort(numbers, 0, n - 1);

    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
}
