#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void prefixSuffixArray(char* pat, int M, int* pps) {
   int length = 0;
   pps[0] = 0;
   int i = 1;
   while (i < M) {
      if (pat[i] == pat[length]) {
         length++;
         pps[i] = length;
         i++;
      } else {
         if (length != 0)
         length = pps[length - 1];
         else {
            pps[i] = 0;
            i++;
         }
      }
   }
}
void KMPAlgorithm(char* text, char* pattern, int *k) {
   int M = strlen(pattern);
   int N = strlen(text);
   int pps[M];
   int out[100] = {0};
   
   int ite = 0;
   prefixSuffixArray(pattern, M, pps);
   int i = 0;
   int j = 0;
   while (i < N) {
      if (pattern[j] == text[i]) {
         j++;
         i++;
      }
      if (j == M) {
         out[ite] = i - j;
         ite = ite + 1;
         j = pps[j - 1];
      }
      else if (i < N && pattern[j] != text[i]) {
         if (j != 0)
         j = pps[j - 1];
         else
         i = i + 1;
      }
   }
   *k = ite;
}
int main() {
   for (int i = 0; i < 10000000; i++) {
      char text[] = "dcpaabtaadaaciaaacdaadrtvaavhaauaalziaastaanfqaaagaaavaaypaalnmaaovaauaaawlaalcaaczaadvaaheaaoaapmaaspaaabaabaaaaa";
      char pattern[] = "aa";
      int k = 0;
      KMPAlgorithm(text, pattern, &k);
   }
   return 0;
}