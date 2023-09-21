#include <string.h>

int is_opts_string(const char *pre, const char *str)
{
  return strncmp(pre, str, strlen(pre)) == 0;
}

int get_int_digit(unsigned long num)
{
  int digit = 0;
  do
  {
    num /= 10;
    digit++;
  } while (num != 0);
  return digit;
}