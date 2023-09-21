#include <stdio.h>
#include <string.h>

#include <opts.h>
#include <common.h>
#include <dir.h>
#include <queue.h>

// TODO: 루트(/) 디렉토리 인식하지 못 하는 문제 수정
int main(int argc, char **argv)
{
  int opts = get_opt_flags(argc, argv);
  queue q;

  init_queue(&q);
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

      enqueue(&q, strdup(argv[i]));
    }

    // 인자가 여러 개 있는 경우, 정렬해서 탐색
    sort_queue(&q);
    // TODO: -R 옵션이 아닌 경우, 각 node 모아서 따로 탐색 돌리는 로직 추가
    while (!is_empty(&q))
    {
      node n = dequeue(&q);

      traverse_dir(n.dir_name, "", &opts);
    }
  }

  return 0;
}