#include <stdlib.h>
#include <queue.h>
#include <file_util.h>

void init_queue(file_queue *queue)
{
  queue->front = queue->tail = NULL;
  queue->count = 0;
}

bool is_empty(file_queue *queue)
{
  return queue->count == 0;
}

void enqueue(file_queue *queue, char *file)
{
  file_node *node = (file_node *)malloc(sizeof(file_node));
  read_file_info(file, &node->file);
  if (is_empty(queue))
  {
    queue->front = node;
  }
  else
  {
    queue->tail->next = node;
  }
  queue->tail = node;
  queue->count++;
}

file_obj dequeue(file_queue *queue)
{
  file_obj file = queue->front->file;

  file_node *del_node = queue->front;
  queue->front = queue->front->next;
  queue->count--;
  free(del_node);

  return file;
}