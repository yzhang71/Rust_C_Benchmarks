#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* longestPalindrome(char* s) {
    
    int len1  = strlen(s);
    int len2 = 2*len1;
    char *tmp = (char*)malloc(sizeof(char)*len2 + 3);  // adding '@'、'$'(as boundary) and '\0'(as end)
    int  *len = (int*)malloc(sizeof(int)*len2 + 3);

    //init
    tmp[0] = '@';
    for(int i = 1; i<= len1; i++) {
       int d         = 2 * i;
       tmp[d - 1] = '#';
       tmp[d]      = s[i - 1];
    }
    tmp[len2 + 1] = '#';
    tmp[len2 + 2] = '$';

    // loop for finding the substring
    int max = 0, max_len = 0, final_id = 0, max_id = 0;
    for(int i = 1; i <= len2; i++) {
       if( max > i ) {
           len[i] = len[2 * max_id - i] >  (max - i) ? (max - i) : len[2 * max_id - i];
       } else {
           len[i] = 1;
       }

       for(; tmp[ i + len[i]] == tmp[i - len[i]]; len[i]++);

       //update max
       if(i + len[i] > max) {
           max = len[i] + i;
           max_id = i;
       }

       //update max_len
       if(len[i] > max_len ) {
           max_len   = len[i];
           final_id  = i;
       }
    }

    // the result is begin with s[(final_id +1)/2 - max_len/2 - 1], the len is max_len - 1
    char *result = NULL;
    final_id = (final_id + 1)/2;
    max_len-=1;
    result = (char*)malloc(sizeof(char)*(max_len + 1));
    memcpy(result, s + final_id - max_len/2 - 1, max_len);
    result[max_len] = '\0';

    return result;
}

/** Driver Code */
int main(int argc, const char *argv[])
{
    double time_spent = 0.0;
 
    clock_t begin = clock();
    for (int i = 0; i < 4000000; i++)
    {

        char arr[] = {"kidcpbtdcyplnmovuawllcczdvheopmspomaramovvhulzistnfiacddrtqagavl"};

        longestPalindrome(arr);

    }
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
    return 0;
}