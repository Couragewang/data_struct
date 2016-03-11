//带头节点的循环链表
#include <stdio.h>

#define _TRUE_ 1
#define _FALSE_ 0
typedef int elem_type;

typedef struct node{
	elem_type data;
	struct node *next;
}node_t, *node_ptr, **node_pptr;

int init_list(node_pptr phead);
int push_back(node_ptr head, elem_type _data);
int pop_back(node_ptr head);
int push_front(node_ptr head, elem_type _data);
int pop_front(node_ptr head);
int is_empty(node_ptr head);
int show_list(node_ptr head);
int clear(node_ptr head);
