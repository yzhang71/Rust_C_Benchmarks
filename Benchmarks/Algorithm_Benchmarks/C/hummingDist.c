#include <string.h>
#include <assert.h>     /// for assert
#include <stdbool.h>    /// for bool
#include <stdio.h>      /// for IO operations
#include <stdlib.h>     /// for dynammic memory allocation
#include <time.h> 
// function to calculate Hamming distance
int hammingDist(char *str1, char *str2)
{
    int i = 0, count = 0;
    while (i < strlen(str1))
    {
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    return count;
}
 
// driver code
int main() 
{
    char str1[] = "geekspracticehguisdhgiiuweyriuwehiiuweyriuwehfwebfuwebguyuheruihgvuyebghuiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueyveuyrghfiuhwuefwebfuwebguyuheruiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueihgvuyebghuyveuyrghfiuhwueihfiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueiwuehuyfgbwuybfviyuwehbiufh";
    char str2[] = "nerdspractiseeruhfiuerhgbgtreughiuewriiuweyriuwehfwebfuwebguyiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueuheruihgvuyebghuyveuyrghfiuhwuehfiuwiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwueehfuibuyweiiuweyriuwehfwebfuwebguyuheruihgvuyebghuyveuyrghfiuhwuebiughneruijhfoweifjwoeijguibhniurteboehjoirwhjeoifhoou";

    int size = 10000000;

    int c = 0;

    double time_spent = 0.0;
 
    clock_t begin = clock();

    for (int i = 0; i < size; i++) {
 
        // function call
        c = hammingDist (str1, str2);
    }
    
    printf("%d\n", c);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
    return 0;
}


