#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dir.h>
#include <opts.h>
#include <print.h>
#include <queue.h>

void traverse_dir(char *dir_name, const char *parent_dir, const int *opts)
{
  DIR *dp;
  struct dirent *p;
  struct stat buf;
  queue *q;

  // 순회 하는 부분
  lstat(dir_name, &buf);
  if (S_ISDIR(buf.st_mode))
  {
    chdir(dir_name);
  }

  dp = opendir(".");

  q = get_folder_elem_queue(dp, dir_name);
  // 출력 하는 부분
  print_folder_header(dir_name, parent_dir, opts);
  print_file(q, opts);
  free(q);

  if ((*opts & R_OPT) == 0)
  {
    return;
  }
  rewinddir(dp);
  while (p = readdir(dp))
  {
    lstat(p->d_name, &buf);
    if (S_ISDIR(buf.st_mode))
    {
      if (strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
      {
        // 경로 출력을 위해서 full path 전달
        char *p_dir;

        if (strcmp(parent_dir, "") == 0)
        {
          p_dir = (char *)malloc((size_t)(strlen(dir_name) + 2));
          p_dir = strdup(dir_name); // parent_dir 가 argv인 경우, 초기화 되지 않은 포인터이므로 strdup 사용
          strcpy(p_dir, dir_name);
        }
        else
        {
          p_dir = (char *)malloc((size_t)(strlen(parent_dir) + 2));
          strcpy(p_dir, parent_dir);
        }
        traverse_dir(p->d_name, p_dir, opts);

        free(p_dir);
      }
    }
  }

  closedir(dp);
  chdir("..");
}

queue *get_folder_elem_queue(DIR *dp, char *d_name)
{
  queue *q = (queue *)malloc(sizeof(queue));
  struct stat buf;
  struct dirent *p;

  init_queue(q);
  lstat(d_name, &buf);

  if (S_ISDIR(buf.st_mode))
  {
    while (p = readdir(dp))
    {
      node n;
      strcpy(n.dir_name, p->d_name);
      lstat(n.dir_name, &n.buf);
      enqueue_node(q, &n);
    }
  }

  return q;
}