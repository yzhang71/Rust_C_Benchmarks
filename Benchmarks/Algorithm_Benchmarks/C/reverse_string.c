#include <string.h>
#include <assert.h>     /// for assert
#include <stdbool.h>    /// for bool
#include <stdio.h>      /// for IO operations
#include <stdlib.h>     /// for dynammic memory allocation

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

// reverse vector of int
int n = 306;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    char *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%c", &numbers[i]);
    }

    int size = 100000000;

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        reverse(numbers, n);

    }
}