#pragma once

//链表的链式实现
#include <iostream>

template <class T>
class myqueue{
	typedef struct _node{
		T _data;
		struct _node *_next;

		_node(const T &_val)
			:_data(_val)
			,_next(NULL)
		{}
	}node_t, *node_p;

	node_p alloc_node(const T &_val)
	{
		node_p tmp = new node_t(_val);
		return tmp;
	}

	void delete_node(node_p &tmp)
	{
		if( tmp ){
			delete tmp;
			tmp = NULL;
		}
	}

	public:
		myqueue()
		{
			head = tail = NULL;
			size = 0;
		}

		void push(const T &_val)
		{
			//队列中没有节点
			if( size == 0 ){
				head = alloc_node(_val);
				tail = head;
			}else{//有节点
				tail->_next = alloc_node(_val);
				tail = tail->_next;
			}
			size++;
		}

		void pop()
		{
			if( size == 0 ){
				return;
			}else if( size == 1 ){
				delete_node(head);
				head = tail = NULL;
			}else{
				node_p tmp = head;
				head = head->_next;
				delete_node(tmp);
			}
			--size;
		}

		const T &back()
		{
			assert(tail);
			return tail->_data;
		}

		const T &front()
		{
			assert(head);
			return head->_data;
		}

		bool empty()
		{
			return size == 0;
		}

		void clear()
		{
			while(size > 0){
				pop();
			}
		}

		size_t queue_size()
		{
			return size;
		}

		void print()
		{
			node_p begin = head;
			std::cout<<"queue head <- ";
			while(begin){
				std::cout<<begin->_data<<" <- ";
				begin = begin->_next;
			}
			std::cout<<"queue tail"<<std::endl;
		}

		~myqueue()
		{
			clear();
		}
	private:
		node_p head; //队列头部
		node_p tail; //队列尾部
		size_t size; //队列中元素个数
};





