#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

struct String {
  char *data;
  int length;
  int size;
} typedef String;

int main() {
  struct timeval st, et;

  gettimeofday(&st,NULL);

  int fd = open("input.txt", O_RDONLY);

  struct stat statbuf;
  int err = fstat(fd, &statbuf);

  char *ptr = mmap(NULL,statbuf.st_size,
            PROT_READ,MAP_SHARED,
            fd,0);

  gettimeofday(&et,NULL);
  int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Read: %d micro seconds\n", elapsed);

  int total_elapsed = elapsed;

  gettimeofday(&st,NULL);

  char buffer[6];
  int pos = 0;

  int max1 = 0;
  int max2 = 0;
  int max3 = 0;

  int currentElfCalories = 0;
  for (int i = 0; i < statbuf.st_size; i++)
  {
    char ch = ptr[i];

    if (ch == '\n') {
      if (pos != 0) {
        buffer[pos] = 0;
        int calories = atoi(buffer);

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

  total_elapsed += elapsed;
  printf("Total: %d micro seconds\n", total_elapsed);

  printf("%d", max1 + max2 + max3);

  munmap(ptr, statbuf.st_size);
  close(fd);
  
  return 0;
}