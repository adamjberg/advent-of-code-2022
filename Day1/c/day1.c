#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct String {
  char *data;
  int length;
  int size;
} typedef String;

int main() {
  struct timeval st, et;

  gettimeofday(&st,NULL);

  FILE * fp = fopen ("input.txt", "r");

  String contents;

  contents.length = 0;
  contents.size = 10375;
  contents.data = malloc(contents.size);

  int num_read = fread(contents.data, 1, contents.size - contents.length, fp);
  contents.length = num_read;

  gettimeofday(&et,NULL);
  int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Read: %d micro seconds\n", elapsed);

  char buffer[6];
  int pos = 0;

  int max1 = 0;
  int max2 = 0;
  int max3 = 0;

  int currentElfCalories = 0;
  for (int i = 0; i < contents.length; i++)
  {
    char ch = contents.data[i];

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

  gettimeofday(&et,NULL);
  elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Part 2: %d micro seconds\n",elapsed);

  printf("%d", max1 + max2 + max3);
  
  return 0;
}