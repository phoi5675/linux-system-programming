#include <stdio.h>

#include <opts.h>
#include <common.h>
#include <dir.h>

int main(int argc, char **argv)
{
  int opts = get_opt_flags(argc, argv);

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
      // '/'가 파일 맨 끝에 있는 경우, 파일 형식 출력 시 "//" 로 출력되므로 제거
      remove_slash_end_of_string(argv[i]);
      // TODO: 여기에서 queue에 담고, 정렬 한 이후에 traverse_dir 함수 호출하도록 변경
      traverse_dir(argv[i], "", &opts);
    }
  }

  return 0;
}