#include  <stdio.h>  
#include <stdlib.h>
 
void gnome_sort(int *array, int size){ 
   int i, tmp; 
   for(i=1; i<size; ){
       if(array[i-1] <= array[i])
           ++i;
       else{
           tmp = array[i];
           array[i] = array[i-1];
           array[i-1] = tmp;
           --i;
           if(i == 0)
               i = 1;
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

    int size = 30000000;

    /* Intializes random number generator */
    // int *arr = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {

        gnome_sort(numbers, n);

    }
}
