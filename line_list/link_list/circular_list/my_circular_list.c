#include <stdlib.h>
#include "my_circular_list.h"

static node_ptr buy_node(elem_type _data)
{
	node_ptr tmp = (node_ptr)malloc(sizeof(node_t));
	if(tmp != NULL){
		tmp->data = _data;
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

int is_empty(node_ptr head)
{
	if( head && head->next == head ){
		return _TRUE_;
	}
	return _FALSE_;
}

int init_list(node_pptr phead)
{
	*phead = buy_node(0);
	if(*phead){
		(*phead)->data = 0;
		(*phead)->next = *phead;
		return 0;
	}
	return 1;
}

int push_back(node_ptr head, elem_type _data)
{
	node_ptr tmp = buy_node(_data);
	if(tmp){
		node_ptr curr = head;
		while(curr&& curr->next != head){
			curr = curr->next;
		}
		tmp->next = curr->next;
		curr->next = tmp;
		return 0;
	}
	return 1;
}

int pop_back(node_ptr head)
{
	if( !is_empty(head) ){
		node_ptr prev = head;
		node_ptr curr = head;
		while(curr && curr->next){
			prev = curr;
			curr = curr->next;
		}
		prev->next = head;
		delete_node(curr);
		return 0;
	}
	return 1;
}

int push_front(node_ptr head, elem_type _data)
{
	node_ptr tmp = buy_node(_data);
	if(tmp){
		tmp->next = head->next;
		head->next = tmp;
		return 0;
	}
	return 1;
}

int pop_front(node_ptr head)
{
	if( !is_empty(head) ){
		node_ptr tmp = head->next;
		head->next = tmp->next;
		delete_node(tmp);
		return 0;
	}
	return 1;
}

int show_list(node_ptr head)
{
	if( !is_empty(head) ){
		node_ptr curr = head->next;
		while(curr != head){
			printf("%d ", curr->data);
			curr = curr->next;
		}
		printf("\n");
	}
	return 0;
}

int clear(node_ptr head)
{
	while(!is_empty(head)){
		pop_front(head);
	}
	return 0;
}

