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

void print_file(DIR *, char *, const char *, const int *);
void set_l_prettier(queue *, l_prettier *);

void print_inode(unsigned long, int, int);
void print_perm(struct stat *, int);
void print_nlink(struct stat *, int, int);
void print_pwd(struct stat *, int, int);
void print_grp(struct stat *, int, int);
void print_size(struct stat *, l_prettier *, int);
void print_time(struct stat *, l_prettier *, int);
void print_name(node *, int);
#endif