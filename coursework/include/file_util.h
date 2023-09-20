#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__

#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

typedef struct file_obj
{
  char file_name[256];
  struct stat st;
} file_obj;

void read_file_info(char *, file_obj *);
#endif