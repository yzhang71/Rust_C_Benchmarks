#include <stdio.h>
#include <stdlib.h>

void Swap(int* a, int* b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void CocktailSort(int* data, int count)
{
    while (1)
    {
        char flag;
        int start[2] = { 1, count - 1 };
        int end[2] = { count, 0 };
        int inc[2] = { 1, -1 };

        for (int it = 0; it < 2; ++it)
        {
            flag = 1;

            for (int i = start[it]; i != end[it]; i += inc[it])
            {
                if (data[i - 1] > data[i])
                {
                    Swap(data + i - 1, data + i);
                    flag = 0;
                }
            }

            if (flag)
                return;
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

    int size = 100000000;

    /* Intializes random number generator */
    for (int i = 0; i < size; i++) {

        CocktailSort(numbers, n);

    }
}
