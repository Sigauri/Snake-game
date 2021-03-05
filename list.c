#include "list.h"
#include "stdlib.h"


struct list *create_list()
{
	struct list *lst = malloc(sizeof(struct list));
	lst->first = lst->last = NULL;
	return lst;
}

void insert_after(struct list *lst, struct node *nd, struct node *new_node)
{	
	new_node->prev = nd;
	if(!nd->next)
	{
		new_node->next = NULL;
		lst->last = new_node;
	}
	else
	{
		new_node->next = nd->next;
		nd->next->prev = new_node;
	}
	nd->next = new_node;
	lst->size++;
}


void insert_before(struct list *lst, struct node *nd, struct node *new_node)
{
	new_node->next = nd;
	if(!nd->prev)
	{
		new_node->prev = NULL;
		lst->first = new_node;
	}
	else
	{
		nd->prev->next = new_node;
		new_node->prev = nd->prev;
	}
	nd->prev = new_node;
	lst->size++;
}

void insert_beginning(struct list *lst, struct node *nd)
{	

	if(!lst->first)
	{
		lst->first = lst->last = nd;
		nd->next = nd->prev = NULL;
		lst->size++;
	}
	else insert_before(lst, lst->first, nd);
}

void insert_end(struct list *lst, struct node *nd)
{
	if(lst->last)
	{
		insert_after(lst, lst->last, nd);
	}
	else
	{
		insert_beginning(lst, nd);
	}
}

void remove_last(struct list *lst)
{
	struct node *last = lst->last;
	if(!last->prev)
	{
		lst->last = lst->first = NULL;	
	}
	else
	{
		last->prev->next = NULL;
		last = last->prev;
	}
}