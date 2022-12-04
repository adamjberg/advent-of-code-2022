#include "str.h"
#include <stdlib.h>

str_t *str_new(size_t capacity)
{
  str_t *str = malloc(sizeof(str_t));

  str->length = 0;
  str->capacity = capacity;
  str->data = malloc(capacity);

  return str;
}

str_t *str_from_c_str(const char *c_str)
{
  int len = strlen(c_str);

  str_t *str = malloc(sizeof(str_t));
  str->length = len;
  str->capacity = len;
  str->data = malloc(len);

  return str;
}

void str_clear(str_t *str) {
  str->length = 0;
}

void str_append_char(str_t *str, char c) {
  if (str->length >= str->capacity - 1)
  {
    return;
  }
  str->data[str->length] = c;
  str->length++;
}

char str_char_at(str_t *str, size_t index)
{
  if (index >= str->length || index < 0)
  {
    return 0;
  }
  return str->data[index];
}

void str_set_char_at(str_t *str, size_t index, char c) {
  if (index >= str->length || index < 0)
  {
    return;
  }

  str->data[index] = c;
}

void str_free(str_t *str)
{
  free(str->data);
  free(str);
}