#ifndef _STR_H_
#define _STR_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

typedef struct str_t
{
  char *data;
  size_t length;
  size_t capacity;
} str_t;

str_t *str_new(size_t capacity);
str_t *str_from_c_str(const char *c_str);
void str_clear(str_t *str);
void str_append_char(str_t *str, char c);
char str_char_at(str_t *str, size_t index);
void str_set_char_at(str_t *str, size_t index, char c);
void str_free(str_t *str);
#endif