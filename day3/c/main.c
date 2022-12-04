// https://github.com/stebucko360/adventOfCode2022/blob/main/day3.js

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

struct String
{
  char *data;
  int length;
  int size;
} typedef String;

int get_dupe_priority(String *str)
{
  bool char_map[53] = {};
  for (int i = 0; i < str->length; i++)
  {
    char c = str->data[i];

    int priority;
    if (c <= 'z' && c >= 'a')
    {
      priority = c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z')
    {
      priority = c - 'A' + 27;
    }

    int half_length = str->length / 2;

    if (i < half_length)
    {
      if (!char_map[priority])
      {
        char_map[priority] = true;
      }
    }
    else
    {
      if (char_map[priority])
      {
        return priority;
      }
    }
  }
  return 0;
}

void part_one(const char *ptr, int length) {
  String line;

  line.length = 0;
  line.size = 50;
  line.data = malloc(line.size);

  int total_priority = 0;

  for (int i = 0; i < length; i++)
  {
    char c = ptr[i];

    if (c == '\n')
    {
      line.data[line.length] = 0;
      int priority = get_dupe_priority(&line);
      total_priority += priority;
      line.length = 0;
    }
    else
    {
      line.data[line.length] = c;
      line.length++;
    }
  }
  printf("%d\n", total_priority);
}

int main()
{
  int fd = open("input.txt", O_RDONLY);

  struct stat statbuf;
  int err = fstat(fd, &statbuf);

  int length = statbuf.st_size;

  char *ptr = mmap(NULL, length,
                   PROT_READ, MAP_SHARED,
                   fd, 0);

  part_one(ptr, length);

  munmap(ptr, statbuf.st_size);
  close(fd);
}