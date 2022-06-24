#include <stdio.h>
#include <limits.h>
#include <stdlib.h>     /// for dynammic memory allocation
#include <time.h> 

// m is size of coins array (number of different coins) 
int minCoins(int coins[], int m, int V, int *k) 
{ 
    // table[i] will be storing the minimum number of coins 
    // required for i value.  So table[V] will have result 
    int table[V+1]; 
  
    // Base case (If given value V is 0) 
    table[0] = 0; 
  
    // Initialize all table values as Infinite 
    for (int i=1; i<=V; i++) 
        table[i] = INT_MAX; 
  
    // Compute minimum coins required for all 
    // values from 1 to V 
    for (int i=1; i<=V; i++) 
    { 
        // Go through all coins smaller than i 
        for (int j=0; j<m; j++) 
          if (coins[j] <= i) 
          { 
              int sub_res = table[i-coins[j]]; 
              if (sub_res != INT_MAX && sub_res + 1 < table[i]) 
                  table[i] = sub_res + 1; 
          } 
    }
    *k = table[V];
    return table[V]; 
} 
  
// Driver program to test above function
int n = 97;

/** Driver Code */
int main(int argc, const char *argv[]) {
    
    int *numbers;

    numbers = malloc(n * sizeof(*numbers));

    for (int i=0; i<n; i++) {
        scanf("%d", &numbers[i]);
    }

    int k = 0;
    int V = 98564;
    double time_spent = 0.0;
 
    clock_t begin = clock();
    for (int i = 0; i < 500; i++)
    {
        
        minCoins(numbers, 97, V, &k);

    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent); 
    return k; 
}
