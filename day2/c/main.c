#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct String {
  char *data;
  int length;
  int size;
} typedef String;

int partOne(String *contents) {
  int score = 0;
  for (int i = 0; i < contents->length; i += 4) {
    char opponent_char = contents->data[i];
    char my_char = contents->data[i + 2];

    int opponent_move_val = opponent_char - 'A' + 1;
    int my_move_val = my_char - 'X' + 1;

    score += my_move_val;

    // DRAW
    if (opponent_move_val == my_move_val) {
      score += 3;
    }
    if (opponent_char == 'A') {
      if (my_char == 'Y') {
        score += 6;
      }
    }
    if (opponent_char == 'B') {
      if (my_char == 'Z') {
        score += 6;
      }
    }
    if (opponent_char == 'C') {
      if (my_char == 'X') {
        score += 6;
      }
    }
  }

  return score;
}

int partTwo(String *contents) {
  int score = 0;
  for (int i = 0; i < contents->length; i += 4) {
    char opponent_char = contents->data[i];
    char my_char = contents->data[i + 2];

    if (my_char == 'Y') {
      score += 3;
    } else if (my_char == 'Z') {
      score += 6;
    }

    int opponent_move_val = opponent_char - 'A' + 1;
    int my_move_val = my_char - 'X' + 1;

    if (opponent_char == 'A') {
      // Y
      score += 2;
    }
    if (opponent_char == 'B') {
      // Z
      score += 3;
    }
    if (opponent_char == 'C') {
      // X
      score += 1;
    }
  }

  return score;
}

int main() {
  int total_elapsed = 0;

  struct timeval st, et;
  gettimeofday(&st,NULL);
  FILE *fp = fopen("input.txt", "r");
  String contents;

  contents.length = 0;
  contents.size = 10000;
  contents.data = malloc(contents.size);

  int num_read = fread(contents.data, 1, contents.size - contents.length, fp);
  contents.length = num_read;

  gettimeofday(&et,NULL);
  int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  total_elapsed += elapsed;
  printf("Read: %d micro seconds\n",elapsed);

  
  printf("%d\n", partOne(&contents));
  gettimeofday(&et,NULL);
  elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  total_elapsed += elapsed;
  printf("Part One: %d micro seconds\n",elapsed);

  gettimeofday(&st,NULL);
  printf("%d\n", partTwo(&contents));
  gettimeofday(&et,NULL);
  elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Part Two: %d micro seconds\n",elapsed);

  total_elapsed += elapsed;

  printf("Total: %d micro seconds", total_elapsed);
}