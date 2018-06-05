#ifndef __VBLIBC_STRING_H
#define __VBLIBC_STRING_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int
is_string_ends_with (
  const char *str,
  const char *tpl
);

int
is_string_starts_with (
  const char *str,
  const char *tpl
);

#ifdef __cplusplus
}
#endif

#endif /* !__VBLIBC_STRING_H */
