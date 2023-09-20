#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <dir.h>
#include <opts.h>
#include <print.h>

void traverse_dir(char *dir_name, const int *opts)
{
  DIR *dp;
  struct dirent *p;
  struct stat buf;

  chdir(dir_name);
  dp = opendir(".");

  // 출력 하는 부분
  // TODO:
  print_file(dp, dir_name, opts);

  // 순회 하는 부분
  rewinddir(dp);
  while (p = readdir(dp))
  {
    lstat(p->d_name, &buf);
    if (S_ISDIR(buf.st_mode))
    {
      if (strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
      {
        traverse_dir(p->d_name, opts);
      }
    }
  }

  closedir(dp);
  chdir("..");
}