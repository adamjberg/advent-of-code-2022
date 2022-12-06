// https://www.reddit.com/r/adventofcode/comments/zc0zta/comment/iyyvbai/?utm_source=share&utm_medium=web2x&context=3
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct
{
  int a, b;
} Pair;
int maxi(int a, int b) { return a > b ? a : b; }

bool Pair_contain(const Pair *a, const Pair *b)
{
  return b->a >= a->a && b->b <= a->b;
}

int Pair_overlap(const Pair *a, const Pair *b)
{
  const Pair *c = a->a < b->a ? a : b;
  const Pair *d = c == a ? b : a;
  return maxi(0, c->b - d->a + 1);
}

int main(void)
{
  Pair a, b;
  int c = 0, o = 0;

  int fd = open("input.txt", O_RDONLY);

  struct stat statbuf;
  int err = fstat(fd, &statbuf);

  char *ptr = mmap(NULL, statbuf.st_size,
                   PROT_READ, MAP_SHARED,
                   fd, 0);

  int pos = 0;
  for (int i = 0; i < statbuf.st_size; i++) {
    if (ptr[i] == '\n') {
      sscanf(ptr[pos], "%d-%d,%d-%d", &a.a, &a.b, &b.a, &b.b);
      c += Pair_contain(&a, &b) || Pair_contain(&b, &a);
      o += !!Pair_overlap(&a, &b);
      pos = i + 1;
    }
  }
  printf("%d %d", c, o);

  return EXIT_SUCCESS;
}