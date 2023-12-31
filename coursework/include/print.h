#ifndef __PRINT_H__
#define __PRINT_H__

#include <dirent.h>
#include <queue.h>

typedef struct l_prettier
{
  int st_ino;
  int nlink;
  int pw_name;
  int gr_name;
  int st_major;
  int st_minor;
  int st_size;
} l_prettier;

void print_folder_header(char *, const char *, const int *);
void print_file(queue *, const int *);
void set_l_prettier(queue *, l_prettier *);
unsigned long get_blk_size(queue *);

void print_inode(unsigned long, int, int);
void print_perm(struct stat *, int);
void print_nlink(struct stat *, int, int);
void print_pwd(struct stat *, int, int);
void print_grp(struct stat *, int, int);
void print_size(struct stat *, l_prettier *, int);
void print_time(struct stat *, l_prettier *, int);
void print_name(node *, int);
#endif