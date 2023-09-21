#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

void init_queue(queue *q)
{
  q->front = q->rear = NULL;
  q->count = 0;
}

int is_empty(queue *q)
{
  return q->count == 0;
}

void enqueue(queue *q, char *d_name)
{
  node *new_node = (node *)malloc(sizeof(node));
  strcpy(new_node->dir_name, d_name);
  new_node->next = NULL;

  if (is_empty(q))
  {
    q->front = new_node;
  }
  else
  {
    q->rear->next = new_node;
  }
  q->rear = new_node;
  q->count++;
}

void enqueue_node(queue *q, node *n)
{
  node *new_node = (node *)malloc(sizeof(node));
  copy_node(new_node, n);
  new_node->next = NULL;

  if (is_empty(q))
  {
    q->front = new_node;
  }
  else
  {
    q->rear->next = new_node;
  }
  q->rear = new_node;
  q->count++;
}

node dequeue(queue *q)
{
  node *n;
  node ret;
  ret.dir_name[0] = '\0'; // 초기화
  if (is_empty(q))
  {
    return ret;
  }

  n = q->front;
  q->front = n->next;

  copy_node(&ret, n);

  free(n);
  q->count--;

  return ret;
}

void copy_node(node *dst, node *src)
{
  if (dst == NULL || src == NULL)
  {
    return;
  }

  strcpy(dst->dir_name, src->dir_name);
  dst->next = src->next;
}

int compare(const void *s1, const void *s2)
{
  return strcmp((char *)s1, (char *)s2);
}
void sort_queue(queue *q)
{
  node *tmp_ary = (node *)malloc(sizeof(node) * q->count);
  int idx = 0;

  while (!is_empty(q))
  {
    node n = dequeue(q);
    copy_node(&tmp_ary[idx++], &n);
  }
  qsort(tmp_ary, idx, sizeof(node), compare);

  for (int i = 0; i < idx; i++)
  {
    enqueue_node(q, &tmp_ary[i]);
  }

  free(tmp_ary);
}

/**
 * 디버그 등의 용도로 queue의 node를 모두 print 하는 함수
 */
void print_queue(queue *q)
{
  node *n;
  if (is_empty(q))
  {
    return;
  }

  n = q->front;
  while (n != NULL)
  {
    printf("dir_name = %s\n", n->dir_name);
    n = n->next;
  }
}