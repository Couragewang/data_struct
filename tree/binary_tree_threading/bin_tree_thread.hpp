#pragma once

#include <iostream>

// 可以证明：在n个结点的二叉链表中含有n+1个空指针。因为含n个结点的二叉链表中含有2n个指针，除了根结点，
// 每个结点都有一个从父结点指向该结点的指针，因此一共使用了n-1个指针，所以在n个结点的二叉链表中含有2n-(n-1)=n+1个空指针。
// 因此，可以利用这些空指针，存放指向结点在某种遍历次序下的前驱和后继结点的指针。这种附加的指针称为线索，
// 加上了线索的二叉链表称为线索链表，相应的二叉树称为线索二叉树。为了区分一个结点的指针是指向其孩子的指针，
// 还是指向其前驱或后继结点的线索，可在每个结点中增加两个线索标志。

using namespace std;

enum pointer_tag{
	THREAD,
	LINK,
};

template<class T>
struct binary_tree_thread_node{
	T data;
	binary_tree_thread_node<T> *left_child;
	binary_tree_thread_node<T> *right_child;
	binary_tree_thread_node<T> *father; //后序遍历？
	pointer_tag left_tag;
	pointer_tag right_tag;

	binary_tree_thread_node(T x)
		:data(x)
		 ,left_child(NULL)
		 ,right_child(NULL)
		 ,left_tag(LINK)
		 ,right_tag(LINK)
	{}
};


template<class T>
class binary_tree_thread{
	public:
		binary_tree_thread()
			:root(NULL)
		{}
		binary_tree_thread(T array[], size_t size)
		{
			int index = 0;
			_create_three(root, array, size, index);
		}
		~binary_tree_thead()
		{}
	private:
		binary_tree_thread_node<T> *buy_node(T val)
		{
			binary_tree_thread_node<T> *tmp = new binary_tree_thead_node<T>(val);
			return tmp;
		}

		_create_tree(binary_tree_thread_node<T> *&root, T array[], size_t size, int &index)
		{
			if(index < size && array[index] != '#'){
		    	root = buy_node(array[index]);
		    	_create_tree(root->left_child, array, size, ++index);
		    	_create_tree(root->right_child, array, size, ++index);
				if(root->left_child){
					root->left_child->father = root;
				}
				if(root->right_child){
					root->left_child->father = root;
				}

			}
		}

		//中序线索化 : 线索化的过程，是需要查找节点的前驱和后继的，而在二叉树中，找节点的前驱后继，需要在遍历中做到
		_in_threading(binary_tree_thread_node<T> *curr, binary_tree_thread_node<T> *&prev)
		{
			if(curr){
				_in_threading(curr->left_child, prev);
				//站在当前节点的角度, prev作为前驱节点，如果可以，被当前节点的左子树指向
				if( curr->left_child == NULL ){
					curr->left_tag = THREAD;
					curr->left_child = prev;
				}
				//站在前驱节点的角度，curr是prev的后继
				if( prev && prev->right == NULL ){
					prev->right_tag = THREAD;
					prev->right_child = curr; //右孩子指向后继节点
				}
				prev = curr;
				_in_threading(curr->right_child, prev);
			}
		}

		//前序线索化
		_prev_threading()
		{}
		//后序线索化
		_post_threading()
		{}
	private:
		binary_tree_thread_node<T> *root;
};














