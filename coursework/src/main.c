#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <opts.h>
#include <common.h>
#include <dir.h>
#include <queue.h>
#include <print.h>

int main(int argc, char **argv)
{
  struct stat buf;
  int opts = get_opt_flags(argc, argv);
  queue file_queue, folder_queue;

  init_queue(&file_queue);
  init_queue(&folder_queue);
  // args 없는 경우, 현재 디렉토리 사용
  if (argc == 1 || (argc == 2 && opts != NO_OPT))
  {
    traverse_dir(".", "", &opts);
  }
  else
  {
    // args로 읽은 파일 로드
    for (int i = 1; i < argc; i++)
    {
      if (is_opts_string("-", argv[i]))
      {
        continue;
      }

      lstat(argv[i], &buf);

      // 파일, 폴더에 따라서 queue를 나눠서 담음
      if (S_ISDIR(buf.st_mode))
      {
        enqueue(&folder_queue, strdup(argv[i]));
      }
      else
      {
        enqueue(&file_queue, strdup(argv[i]));
      }
    }

    // 인자가 여러 개 있는 경우, 정렬해서 탐색
    sort_queue(&file_queue);
    sort_queue(&folder_queue);

    // 옵션에 맞게 file queue 먼저 출력
    print_file(&file_queue, &opts);

    if (!is_empty(&folder_queue))
    {
      printf("\n\n");
    }

    while (!is_empty(&folder_queue))
    {
      node n = dequeue(&folder_queue);

      traverse_dir(n.dir_name, "", &opts);
    }
  }
  if ((opts & l_OPT) == 0)
  {
    printf("\n");
  }

  return 0;
}