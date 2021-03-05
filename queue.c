#include "stdlib.h"
#include "queue.h"

struct queue *create_queue()
{
	struct queue *q = malloc(sizeof(struct queue));
	q->lst = create_list();
	q->lst->size = 0;
	q->lst->first = q->lst->last = NULL;
	return q;
}

void enqueue(struct queue *q, int value)
{
	struct node *nd = malloc(sizeof(struct node));
	nd->value = value;
	insert_end(q->lst, nd);
}

int dequeue(struct queue *q)
{
	int tmp = q->lst->first->value;
	if(q->lst->first->next)q->lst->first = q->lst->first->next;
	remove_node(q->lst, q->lst->first);
	return tmp;
}

int peek(struct queue *q)
{
	if(q->lst->first) return q->lst->first->value;
	return 0;
}