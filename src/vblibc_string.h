#ifndef __VBLIBC_STRING_H
#define __VBLIBC_STRING_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int
vb_string_is_ends_with (
  const char *str,
  const char *tpl
);

int
vb_string_is_starts_with (
  const char *str,
  const char *tpl
);

#ifdef __cplusplus
}
#endif

#endif /* !__VBLIBC_STRING_H */
