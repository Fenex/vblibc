#include <stddef.h>
#include "vblibc_string.h"

int
is_string_ends_with (
  const char *str,
  const char *tpl
) {
  if (str == NULL || tpl == NULL)
    return 0;

  int str_len = strlen(str);
  int tpl_len = strlen(tpl);
  if (str_len < tpl_len)
    return 0;

  for (; tpl_len >= 0; str_len--, tpl_len--) {
    if (*(str + str_len) != *(tpl + tpl_len))
      return 0;
  }

  return 1;
}

int
is_string_starts_with (
  const char *str,
  const char *tpl
) {
  const char *p;
  if (str == NULL || tpl == NULL)
    return 0;

  int str_len = strlen(str);
  int tpl_len = strlen(tpl);
  if (str_len < tpl_len)
    return 0;
  
  for (p = tpl; p <= tpl; str++, p++) {
    if (*str != *p)
      return 0;
  }

  return 1;
}
