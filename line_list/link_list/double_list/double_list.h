#include <stdio.h>
#include <stdlib.h>

#define _FALSE_ 0
#define _TRUE_  1

typedef int elem_type;
typedef struct _node{
	elem_type data;
	struct _node *prev;
	struct _node *next;
}node_t, *node_ptr, **node_pptr;

//带头节点，并且带有头指针，尾指针的循环双链表
typedef struct dlist{
	node_ptr head;
	node_ptr tail;
	int    size;
}dlist_t, *dlist_ptr;

// 初始化
int init_dlist(dlist_ptr dlist);

// 头插/头删/尾插/尾删
int push_front(dlist_ptr dlist, elem_type _data);
int pop_front(dlist_ptr dlist);
int push_back(dlist_ptr dlist, elem_type _data);
int pop_back(dlist_ptr dlist);

// 插入/查找/删除
int insert(dlist_ptr dlist, node_ptr pos, elem_type _data);
node_ptr find(dlist_ptr dlist , elem_type _data);
int erase(dlist_ptr dlist, node_ptr _n);
//void reverse();

// 清除/打印/判空
int clear(dlist_ptr dlist);
int show_dlist(dlist_ptr dlist);
int is_empty(dlist_ptr dlist);
