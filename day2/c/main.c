#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
  char *data;
  int length;
  int size;
} typedef String;

int partOne() {
  FILE *fp = fopen("input.txt", "r");
  String contents;

  contents.length = 0;
  contents.size = 10000;
  contents.data = malloc(contents.size);

  int num_read = fread(contents.data, 1, contents.size - contents.length, fp);
  contents.length = num_read;

  int score = 0;
  for (int i = 0; i < contents.length; i += 4) {
    char opponent_char = contents.data[i];
    char my_char = contents.data[i + 2];

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

int main() {
  printf("%d", partOne());
}