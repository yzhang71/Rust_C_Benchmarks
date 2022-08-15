#include <string.h>
#include <assert.h>     /// for assert
#include <stdbool.h>    /// for bool
#include <stdio.h>      /// for IO operations
#include <stdlib.h>     /// for dynammic memory allocation
#include <time.h> 
// reverse string
void reverse(char s[], int length)
{
    int c;
    int i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// reverse vector
int n = 306;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    char *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%c", &numbers[i]);
    }

    int size = 100000000;
    double time_spent = 0.0;
 
    clock_t begin = clock();
    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        reverse(numbers, n);

    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
}