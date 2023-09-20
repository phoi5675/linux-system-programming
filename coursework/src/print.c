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
    // TODO: 이 부분에서 파일 읽은 후 관련 정보 queue에 저장하는 부분 추가
    // TODO: 이 부분에서 출력 옵션에 따라 출력 바뀌게 하는 부분 추가
    printf("%s\t", p->d_name);
  }
  printf("\n\n");
}
