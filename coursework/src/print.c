#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include <print.h>
#include <opts.h>
#include <queue.h>
#include <common.h>

void print_folder_header(char *d_name, const char *parent_dir, const int *opts)
{
  // -R 옵션 사용 시, 상위 폴더 경로 출력 용도로 concat
  char *p_dir = (char *)malloc((size_t)(strlen(parent_dir) + 2));
  strcpy(p_dir, parent_dir);
  if (strcmp(p_dir, "") != 0 && (p_dir[strlen(p_dir) - 1] != '/'))
  {
    strcat(p_dir, "/");
  }

  if (*opts & R_OPT || *opts & MUL_ARG_OPT)
  {
    printf("%s%s:\n", p_dir, d_name);
  }
  free(p_dir);
}
void print_file(queue *q, const int *opts)
{
  l_prettier *lp = (l_prettier *)calloc(1, sizeof(l_prettier));

  sort_queue(q);

  // 1. l opts 인 경우, alignment 하는 옵션
  set_l_prettier(q, lp);

  if (*opts & l_OPT)
  {
    printf("total %lu\n", get_blk_size(q));
  }
  while (!is_empty(q))
  {
    node n = dequeue(q);

    // -a 옵션이 아닌 경우, . 파일 숨김 처리
    if (((*opts & a_OPT) == 0) && (strncmp(n.dir_name, ".", 1) == 0))
    {
      continue;
    }

    // 1. l opts의 형식에 맞게 출력
    print_inode(n.buf.st_ino, lp->st_ino, *opts);
    print_perm(&n.buf, *opts);
    print_nlink(&n.buf, lp->nlink, *opts);
    print_pwd(&n.buf, lp->pw_name, *opts);
    print_grp(&n.buf, lp->gr_name, *opts);
    print_size(&n.buf, lp, *opts);
    print_time(&n.buf, lp, *opts);
    print_name(&n, *opts);
  }

  printf("\n");

  free(lp);
}

void set_l_prettier(queue *q, l_prettier *lp)
{
  struct group *grp;
  struct passwd *pwd;
  node *n = q->front;

  if (is_empty(q))
  {
    return;
  }

  while (n != NULL)
  {
    int st_size;
    int st_major = 0;
    int st_minor = 0;

    pwd = getpwuid(n->buf.st_uid);
    grp = getgrgid(n->buf.st_gid);

    if (S_ISCHR(n->buf.st_mode) || S_ISBLK(n->buf.st_mode))
    {
      // major, minor 숫자 자리수 + ", "(쉼표, 띄어쓰기) 자리수 추가
      st_major = get_int_digit((n->buf.st_rdev >> 8) & 0xff);
      st_minor = get_int_digit((n->buf.st_rdev) & 0xff);
      st_size = st_major + st_minor + 2;
    }
    else
    {
      st_size = get_int_digit(n->buf.st_size);
    }

    lp->st_ino = MAX(lp->st_ino, get_int_digit(n->buf.st_ino));
    lp->nlink = MAX(lp->nlink, get_int_digit(n->buf.st_nlink));
    lp->pw_name = MAX(lp->pw_name, strlen(pwd->pw_name));
    lp->gr_name = MAX(lp->gr_name, strlen(grp->gr_name));
    lp->st_major = MAX(lp->st_major, st_major);
    lp->st_minor = MAX(lp->st_minor, st_minor);
    lp->st_size = MAX(lp->st_size, st_size);

    n = n->next;
  }
}

unsigned long get_blk_size(queue *q)
{
  node *n = q->front;
  unsigned long ret = 0;
  if (is_empty(q))
  {
    return 0;
  }

  while (n != NULL)
  {
    ret += n->buf.st_blocks;
    n = n->next;
  }
  return ret >> 1;
}

void print_inode(unsigned long inode, int width, int opts)
{
  if ((opts & i_OPT) == 0)
  {
    return;
  }

  printf("%*lu ", width, inode);
}

void print_perm(struct stat *buf, int opts)
{
  int i;
  char perm[] = "----------";
  char rwx[] = "rwx";
  char sst[] = "sst";

  if ((opts & l_OPT) == 0)
  {
    return;
  }

  if (S_ISDIR(buf->st_mode))
    perm[0] = 'd';
  else if (S_ISCHR(buf->st_mode))
    perm[0] = 'c';
  else if (S_ISBLK(buf->st_mode))
    perm[0] = 'b';
  else if (S_ISFIFO(buf->st_mode))
    perm[0] = 'p';
  else if (S_ISLNK(buf->st_mode))
    perm[0] = 'l';
  else if (S_ISSOCK(buf->st_mode))
    perm[0] = 's';

  for (i = 0; i < 9; i++)
  {
    if ((buf->st_mode >> (8 - i)) & 0x1)
    {
      perm[1 + i] = rwx[i % 3];
    }
  }
  for (i = 0; i < 3; i++)
  {
    if ((buf->st_mode >> (11 - i)) & 0x1)
    {
      if (perm[(i + 1) * 3] == '-')
        perm[(i + 1) * 3] = sst[i] - ('a' - 'A');
      else
        perm[(i + 1) * 3] = sst[i];
    }
  }
  printf("%s ", perm);
}

void print_nlink(struct stat *buf, int width, int opts)
{
  if ((opts & l_OPT) == 0)
  {
    return;
  }
  printf("%*lu ", width, buf->st_nlink);
}

void print_pwd(struct stat *buf, int width, int opts)
{
  if ((opts & l_OPT) == 0)
  {
    return;
  }
  struct passwd *pwd = getpwuid(buf->st_uid);

  printf("%*s ", width, pwd->pw_name);
}

void print_grp(struct stat *buf, int width, int opts)
{
  if ((opts & l_OPT) == 0)
  {
    return;
  }
  struct group *grp = getgrgid(buf->st_gid);

  printf("%-*s", width, grp->gr_name);
}

void print_size(struct stat *buf, l_prettier *lp, int opts)
{
  if ((opts & l_OPT) == 0)
  {
    return;
  }
  if (S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode))
  {
    printf("%*lu, %*lu ",
           lp->st_major, (buf->st_rdev >> 8) & 0xff,
           lp->st_minor, (buf->st_rdev & 0xff));
  }
  else
  {
    printf("%*lu ", lp->st_size + 1, buf->st_size);
  }
}

void print_time(struct stat *buf, l_prettier *lp, int opts)
{
  if ((opts & l_OPT) == 0)
  {
    return;
  }
  struct tm *tmp = localtime(&buf->st_mtime);
  char *mon;

  switch (tmp->tm_mon)
  {
  case 0:
    mon = "Jan";
    break;
  case 1:
    mon = "Feb";
    break;
  case 2:
    mon = "Mar";
    break;
  case 3:
    mon = "Apr";
    break;
  case 4:
    mon = "May";
    break;
  case 5:
    mon = "Jun";
    break;
  case 6:
    mon = "Jul";
    break;
  case 7:
    mon = "Aug";
    break;
  case 8:
    mon = "Sep";
    break;
  case 9:
    mon = "Oct";
    break;
  case 10:
    mon = "Nov";
    break;
  case 11:
    mon = "Dec";
    break;
  default:
    mon = "";
  }
  printf("%s %2d %02d:%02d ", mon, tmp->tm_mday, tmp->tm_hour, tmp->tm_min);
}

void print_name(node *n, int opts)
{
  if ((opts & l_OPT) != 0)
  {
    if (S_ISLNK(n->buf.st_mode))
    {
      char buff[256];
      int ret;
      ret = readlink(n->dir_name, buff, sizeof buff);
      buff[ret] = 0;
      printf("%s -> %s\n", n->dir_name, buff);
    }
    else
    {
      printf("%s\n", n->dir_name);
    }
  }
  else
  {
    if (opts & R_OPT)
    {
      printf("%s\n", n->dir_name);
    }
    else
    {
      printf("%s\t", n->dir_name);
    }
  }
}