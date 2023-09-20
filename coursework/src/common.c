#include <string.h>

int is_opts_string(const char *pre, const char *str)
{
  return strncmp(pre, str, strlen(pre)) == 0;
}