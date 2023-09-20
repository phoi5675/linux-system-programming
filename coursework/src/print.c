#include <stdio.h>

#include <print.h>
#include <opts.h>

void print_file(DIR *dp, char *d_name, const int *opts)
{
  struct dirent *p;
  printf("%s:\n", d_name);
  while (p = readdir(dp))
  {
    printf("%s\t", p->d_name);
  }
  printf("\n");
}
