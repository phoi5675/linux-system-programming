#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct node
{
  char dir_name[256];
  struct node *next;
  struct stat buf;
} node;

typedef struct queue
{
  int count;
  node *front;
  node *rear;
} queue;

void init_queue(queue *);
int is_empty(queue *);
void enqueue(queue *, char *);
void enqueue_node(queue *, node *);
node dequeue(queue *);
void copy_node(node *, node *);
void sort_queue(queue *);
void print_queue(queue *);
#endif