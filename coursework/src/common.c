#include <string.h>

int is_opts_string(const char *pre, const char *str)
{
  return strncmp(pre, str, strlen(pre)) == 0;
}
void remove_slash_end_of_string(char *str)
{
  int len = strlen(str);
  if (str[len - 1] == '/')
  {
    str[len - 1] = '\0';
  }
}