#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <file_util.h>

typedef struct file_node
{
  file_obj file;
  struct file_node *next;
} file_node;

typedef struct file_queue
{
  file_node *front;
  file_node *tail;
  int count;
} file_queue;

void init_queue(file_queue *);
bool is_empty(file_queue *);
void enqueue(file_queue *, char *);
file_obj dequeue(file_queue *);
#endif