#include "list.h"

struct queue
{
	int size;
	struct list *lst;
};	

void enqueue(struct queue *q, int value);

int dequeue(struct queue *q);

int peek(struct queue *q);

struct queue *create_queue();