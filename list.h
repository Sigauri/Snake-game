struct list
{
	struct node *first;
	struct node *last;
	int size;
};

struct node
{
	int *values;
	struct node *next;
	struct node *prev;
};

struct list *create_list();
void insert_before(struct list *lst, struct node *nd, struct node *new_node);
void insert_after(struct list *lst, struct node *nd, struct node *new_node);
void insert_beginning(struct list *lst, struct node *nd);
void insert_end(struct list *lst, struct node *nd);
void remove_last(struct list *lst);