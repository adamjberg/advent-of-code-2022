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
#include "str.h"

int get_dupe_priority(str_t *str)
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

void part_one(const char *ptr, int length)
{
  str_t *line = str_new(50);

  int total_priority = 0;

  for (int i = 0; i < length; i++)
  {
    char c = ptr[i];

    if (c == '\n')
    {
      int priority = get_dupe_priority(line);
      total_priority += priority;
      str_clear(line);
    }
    else
    {
      str_append_char(line, c);
    }
  }

  free(line);

  printf("%d\n", total_priority);
}

void part_two(const char *ptr, int length)
{
  int elf_index = 0;

  str_t *elf_lines[3];
  bool char_map[3][53] = {};

  for (int i = 0; i < 3; i++)
  {
    elf_lines[i] = str_new(50);
  }

  int priority_sum = 0;

  for (int i = 0; i < length; i++)
  {
    char c = ptr[i];

    if (c == '\n')
    {
      elf_index++;
      if (elf_index >= 3)
      {
        for (int i = 0; i < 3; i++)
        {
          elf_lines[i]->length = 0;
        }

        elf_index = 0;
      }
    }
    else
    {
      elf_lines[elf_index]->data[elf_lines[elf_index]->length] = c;
      elf_lines[elf_index]->length++;
    }
  }

  for (int i = 0; i < 3; i++)
  {
    str_free(elf_lines[i]);
  }
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