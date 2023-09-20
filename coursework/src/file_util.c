#include <sys/stat.h>
#include <string.h>
#include <file_util.h>

void read_file_info(char *file, file_obj *f_obj)
{
  strcpy(f_obj->file_name, file);
  lstat(file, &(f_obj->st));
}