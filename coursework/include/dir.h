#ifndef __DIR_H__
#define __DIR_H__

#include <dirent.h>

#include <queue.h>

void traverse_dir(char *, const char *, const int *);

queue *get_folder_elem_queue(DIR *, char *);
#endif