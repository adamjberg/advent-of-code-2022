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

int get_priority_for_char(char c) {
  int priority;
    if (c <= 'z' && c >= 'a')
    {
      priority = c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z')
    {
      priority = c - 'A' + 27;
    }
    return priority;
}

int get_dupe_priority(str_t *str)
{
  bool char_map[53] = {};
  for (int i = 0; i < str->length; i++)
  {
    char c = str->data[i];

    int priority = get_priority_for_char(c);

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

  for (int char_index = 0; char_index < length; char_index++)
  {
    char c = ptr[char_index];

    if (c == '\n')
    {
      if (elf_index >= 2)
      {
        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < elf_lines[i]->length; j++) {
            char c = str_char_at(elf_lines[i], j);
            int priority = get_priority_for_char(c);
            char_map[i][priority] = true;
          }
        }

        str_t *all_characters = str_from_c_str("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWYZ");
        for (int i = 0; i < all_characters->length; i++) {
          char c = str_char_at(all_characters, i);
          int priority = get_priority_for_char(c);
          bool found = true;
          for (int j = 0; j < 3; j++)
          {
            if (!char_map[j][priority]) {
              found = false;
            }
          }

          if (found) {
            priority_sum += priority;
          }
        }
        str_free(all_characters);

        for (int i = 0; i < 3; i++)
        {
          str_clear(elf_lines[i]);
          memset(char_map[i], 0, 53);
        }

        elf_index = 0;
      } else {
        elf_index++;
      }
    }
    else
    {
      str_append_char(elf_lines[elf_index], c);
    }
  }

  for (int i = 0; i < 3; i++)
  {
    str_free(elf_lines[i]);
  }

  printf("%d\n", priority_sum);
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

  part_two(ptr, length);

  munmap(ptr, statbuf.st_size);
  close(fd);
}