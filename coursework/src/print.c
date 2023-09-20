#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <print.h>
#include <opts.h>

void print_file(DIR *dp, char *d_name, const char *parent_dir, const int *opts)
{
  struct dirent *p;
  char *p_dir = (char *)malloc((size_t)(strlen(parent_dir) + 2));
  strcpy(p_dir, parent_dir);
  if (strcmp(p_dir, "") != 0)
  {
    strcat(p_dir, "/");
  }
  printf("%s%s:\n", p_dir, d_name);
  while (p = readdir(dp))
  {
    printf("%s\t", p->d_name);
  }
  printf("\n\n");
}
