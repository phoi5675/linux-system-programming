#include <stdio.h>

#include <opts.h>
#include <file_util.h>
#include <common.h>
#include <queue.h>

/*
 * 옵션 설명
  ‘-a’
  ‘--all’
    In directories, do not ignore file names that start with ‘.’.
  ‘-i’
  ‘--inode’
    Print the inode number (also called the file serial number and
    index number) of each file to the left of the file name.  (This
    number uniquely identifies each file within a particular file
    system.)
  ‘-l’
  ‘--format=long’
  ‘--format=verbose’
    In addition to the name of each file, print the file type, file
    mode bits, number of hard links, owner name, group name, size, and
    timestamp (*note Formatting file timestamps::), normally the
    modification time.  Print question marks for information that
    cannot be determined.
  ‘-R’
  ‘--recursive’
    List the contents of all directories recursively.
 */
int main(int argc, char **argv)
{
  int opts = get_opt_flags(argc, argv);
  file_queue queue;

  init_queue(&queue);

  /*
   * ls 실행 시 폴더 또는 argv의 폴더/파일에 대해 enqueue
   */
  // args 없는 경우, 현재 디렉토리 사용
  if (argc == 1 || (argc == 2 && opts == NO_OPT))
  {
    enqueue(&queue, ".");
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
      enqueue(&queue, argv[i]);
    }
  }

  // -R 옵션 있는 경우, 재귀적으로 파일 읽기
  // 옵션 따라서 출력
  return 0;
}