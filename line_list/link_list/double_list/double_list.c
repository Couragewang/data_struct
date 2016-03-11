#include "double_list.h"

static node_ptr buy_node(elem_type _data)
{
	node_ptr tmp = (node_ptr)malloc(sizeof(node_t));
	if(tmp){
		tmp->data = _data;
		tmp->prev = NULL;
		tmp->next = NULL;
	}
	return tmp;
}

static void delete_node(node_ptr _n)
{
	if(_n){
		free(_n);
		_n = NULL;
	}
}

int is_empty(dlist_ptr dlist)
{
	if( dlist && dlist->head && dlist->head == dlist->tail ){
		return _TRUE_;
	}
	return _FALSE_;
}

// 初始化
int init_dlist(dlist_ptr dlist)
{
	int res = _FALSE_;
	node_ptr tmp = buy_node(0);
	if(tmp){
		dlist->head = tmp;
		dlist->tail = tmp;
		dlist->size = 0;
		tmp->prev    = tmp;
		tmp->next    = tmp;
		res = _TRUE_;
	}
	return res;
}

// 头插/头删/尾插/尾删
int push_front(dlist_ptr dlist, elem_type _data)
{
	node_ptr tmp = buy_node(_data);
	if(tmp){
		if( is_empty(dlist) ){
			tmp->next = dlist->head;
			tmp->prev = dlist->head;
			dlist->head->next = tmp;
			dlist->head->prev = tmp;
			dlist->tail = tmp;
			dlist->size++;
		}else{
    		tmp->next = dlist->head->next;
    		tmp->prev = dlist->head;
    		dlist->head->next->prev = tmp;
    		dlist->head->next = tmp;
    		(dlist->size)++;
		}
    	return _TRUE_;
	}
	return _FALSE_;
}

int pop_front(dlist_ptr dlist)
{
	if( !is_empty(dlist) ){
		node_ptr tmp = NULL;
		if(dlist->size == 1){
			tmp = dlist->head->next;
			dlist->head->next = dlist->head;
			dlist->head->prev = dlist->head;
			dlist->tail = dlist->head;
		}else{
	    	tmp = dlist->head->next;
	    	dlist->head->next = tmp->next;
	    	tmp->next->prev = dlist->head;
		}
	    delete_node(tmp);
		return _TRUE_;
	}
	return _FALSE_;
}

int push_back(dlist_ptr dlist, elem_type _data)
{
	node_ptr tmp = buy_node(_data);
	if(tmp){
		tmp->prev = dlist->tail;
		tmp->next = dlist->head;
		dlist->tail->next = tmp;
		dlist->tail = tmp;
		dlist->size++;
		return _TRUE_;
	}
	return _FALSE_;
}

int pop_back(dlist_ptr dlist)
{
	node_ptr tmp = NULL;
	if( !is_empty(dlist) ){
		tmp = dlist->tail;
		dlist->tail = tmp->prev;
		dlist->tail->next = dlist->head;
		dlist->head->prev = dlist->tail;
		delete_node(tmp);
		return _TRUE_;
	}
	return _FALSE_;
}

// 插入/查找/删除
int insert(dlist_ptr dlist, node_ptr pos, elem_type _data)
{
	node_ptr start = dlist->head->next;//指向第一个有效节点
	while( start && start != dlist->head && start != pos ){
		start = start->next;
	}
	if(start && start != dlist->head && start == pos){
		node_ptr tmp = buy_node(_data);
		if(tmp){
			//1. 插入的节点是尾节点
			if(pos == dlist->tail){
				tmp->prev = dlist->tail;
				tmp->next = dlist->head;
				dlist->tail->next = tmp;
				dlist->head->prev = tmp;
				dlist->tail = tmp;
			}else{
				//2. 插入的节点是正常节点
				tmp->next = pos->next;
				tmp->prev = pos;
				pos->next->prev = tmp;
				pos->next = tmp;
			}
			return _TRUE_;
		}
	}
	return _FALSE_;
}

node_ptr find(dlist_ptr dlist , elem_type _data)
{
	if( !is_empty(dlist) ){
		node_ptr start = dlist->head->next;
		while(start != dlist->head){
			if(start->data == _data){
				return start;
			}
			start = start->next;
		}
	}
	return NULL;
}

int erase(dlist_ptr dlist, node_ptr _n)
{
	node_ptr start = dlist->head->next;
	while(start != dlist->head){
		if(start == _n){
			//1. 删除的是尾节点
			if(_n == dlist->tail){
				return pop_back(dlist);
			}else{
				//2. 删除的是普通节点
				_n->prev->next = _n->next;
				_n->next->prev = _n->prev;
				delete_node(_n);
			}
			return _TRUE_;
		}
	}
	return _FALSE_;
}

//void reverse();

// 清除/打印
int clear(dlist_ptr dlist)
{
	while( !is_empty(dlist) ){
		pop_front(dlist);
	}
	delete_node(dlist->head);
	dlist->head = NULL;
	dlist->tail = NULL;
	dlist->size = 0;
	return _TRUE_;
}

int show_dlist(dlist_ptr dlist)
{
	if( !is_empty(dlist) ){
		node_ptr start = dlist->head->next;
		while(start != dlist->head){
			printf("%d\t", start->data);
			start = start->next;
		}
		printf("\n");
	}
	return _TRUE_;
}
















