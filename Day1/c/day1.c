#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE * fp = fopen ("input.txt", "r");

  char ch;
  char buffer[6];
  int pos = 0;

  int max1 = 0;
  int max2 = 0;
  int max3 = 0;

  int currentElfCalories = 0;
  while((ch = getc(fp)) != EOF)
  {
    if (ch == '\n') {
      if (pos != 0) {
        int calories;
        sscanf(buffer, "%d", &calories);
        memset(buffer, 0, sizeof(buffer));

        currentElfCalories += calories;

        pos = 0;
      } else {
        if (currentElfCalories > max1) {
          max2 = max1;
          max1 = currentElfCalories;
        } else if (currentElfCalories > max2) {
          max3 = max2;
          max2 = currentElfCalories;
        } else if (currentElfCalories > max3) {
          max3 = currentElfCalories;
        }
        currentElfCalories = 0;
      }
      
    } else {
      buffer[pos] = ch;
      pos++;
    }
  } 

  printf("%d", max1 + max2 + max3);
  
  return 0;
}