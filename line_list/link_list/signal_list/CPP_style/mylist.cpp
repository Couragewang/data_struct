#include <iostream>
#include "mylist.h"

using namespace std;

node_ptr mylist::buy_node(elem_type _data)
{
	node_ptr tmp = (node_ptr)malloc(sizeof(node_t));
	if( tmp != NULL ){
		tmp->data = _data;
		tmp->next = NULL;
	}
	return tmp;
}

int mylist::delete_node(node_ptr _n)
{
	if( _n ){
    	free(_n);
    	_n = NULL;
	}
	return 0;
}

void mylist::list_init()
{
	head = NULL;//不带头节点，设置为NULL即可
}

int mylist::is_empty()
{
	return (head == NULL? true : false);
}

int mylist::push_front(elem_type _data)
{
	node_ptr tmp = buy_node(_data);
	if(is_empty()){
		head = tmp;
	}else{
		tmp->next = head;
		head = tmp;
	}
	return 0;
}

int mylist::pop_front()
{
	if(is_empty()){
		return 1; //empty, 没有数据
	}else{
		node_ptr tmp = head;
		head = head->next;
		delete_node(tmp);
	}
	return 0;
}

int mylist::push_back(elem_type _data)
{
	node_ptr tmp = buy_node(_data);
	if( !head ){
		head = tmp;
		return 0;
	}
	node_ptr p = head;
	while( p && p->next ){
		p = p->next;
	}
	p = tmp;
	return 0;
}

int mylist::pop_back()
{
	int res = 1;
	if( !is_empty() ){
		if( head->next == NULL){//只有一个节点
			delete_node(head);
			head = NULL;
		}
		node_ptr curr = head;
		node_ptr prev = curr;
		while(curr->next){
			prev = curr;
			curr = curr->next;
		}

		delete_node(prev->next);
		prev->next = NULL;
		res = 0;
	}
	return res;
}

int mylist::clear()
{
	while(head){
		pop_front();
	}
	return 0;
}

int mylist::insert(node_ptr pos, elem_type _data)//节点之后插入
{
	node_ptr tmp = buy_node(_data);
	if(tmp){
		if( is_empty() ){
			head = tmp;
			return 0;
		}else{
			node_ptr curr = head;
			while(curr){
				if(curr == pos){
					tmp->next = curr->next;
					curr->next = tmp;
					return 0;
				}
				curr = curr->next;
			}
		}
	}
	return 1;
}

int mylist::size()
{
	node_ptr curr = head;
	int _size = 0;
	while(curr){
		_size++;
		curr = curr->next;
	}
	return _size;
}

int mylist::get_elem(int i, elem_type *_data)
{
	node_ptr curr = head;
	int pos = 0;
	while(curr){
		pos++;
		if(pos == i){
			*_data = curr->data;
			return 0;
		}
		curr = curr->next;
	}
	return 1;
}

int mylist::find(elem_type _data, node_pptr _node/*output*/)
{
	node_ptr curr = head;
	while(curr){
		if( curr->data == _data ){
			*_node = curr;
			return 0;
		}
		curr = curr->next;
	}
	return 1;
}

int mylist::erase(node_ptr _erase_node)
{
	if(head == _erase_node){
		node_ptr tmp = head;
		head = head->next;
		delete_node(tmp);
		return 0;
	}
	node_ptr curr = head;
	node_ptr prev = curr;
	while(curr){
		if(curr == _erase_node){
			prev->next = curr->next;
			delete_node(curr);
			return 0;
		}
		prev = curr;
		curr = curr->next;
	}
	return 1;
}

int mylist::remove_val(elem_type _val)
{
	return 0;
}

void mylist::show_list()
{
	node_ptr curr = head;
	while( curr ){
		cout<<curr->data<<" ";
		curr = curr->next;
	}
	cout<<endl;
}

mylist::mylist()
{
	list_init();
}

mylist::~mylist()
{
	clear();
}



