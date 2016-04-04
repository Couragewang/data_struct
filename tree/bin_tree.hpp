// \@实现二叉树的基本操作
#pragma once

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template<class T>
struct bin_tree_node{
	T data;                 //数据
	bin_tree_node<T> *left_child; //左孩子
	bin_tree_node<T> *right_child;//右孩子

	bin_tree_node(const T &_x)
		:data(_x),
		left_child(NULL),
		right_child(NULL)
	{}
};

template<class T>
class bin_tree{
	private:

		void visit(const T &_val)
		{
			cout<<_val<<' ';
		}

		bin_tree_node<T> *_buy_node(const T &_val)
		{
			bin_tree_node<T> *tmp = new bin_tree_node<T>(_val);
			return tmp;
		}

		//先序建立二叉树
		bin_tree_node<T> *_create_bin_tree(const T *_arr, const size_t &_size, size_t &_index)
		{
			bin_tree_node<T> *tmp = NULL;
			if(_index < _size && _arr[_index] != '#'){
				tmp  = _buy_node(_arr[_index]);
				tmp->left_child = _create_bin_tree(_arr, _size, ++_index);
				tmp->right_child = _create_bin_tree(_arr, _size, ++_index);
			}
			return tmp;
		}

		//非递归先顺建立二叉树
//		bin_tree_node<T> *_create_bin_tree_nr(const T* _arr, const size_t &_size)
//		{
//			int i = 0;
//			bin_tree_node<T> *tmp = NULL;
//			while( _arr[i] != '\0' ){
//				if(_arr[i++] != '#'){
//					continue;
//				}
//				tmp = _buy_node(arr[i]);
//			}
//		}

		//先序遍历二叉树
		void _prev_order(bin_tree_node<T> *&_root)
		{
			if( NULL == _root ){
				return;
			}
			visit(_root->data); //先访问当前数据
			_prev_order(_root->left_child); //中间访问左子树
			_prev_order(_root->right_child);//最后访问右子树
		}

		//中序遍历二叉树
		void _in_order(bin_tree_node<T> *&_root)
		{
			if( NULL == _root ){
				return;
			}
			_in_order(_root->left_child); //先访问左子树
			visit(_root->data);           //中间访问节点
			_in_order(_root->right_child);//最后访问右子树
		}

		//后序遍历二叉树
		void _post_order(bin_tree_node<T> *&_root)
		{
			if(NULL == _root){
				return;
			}
		    _post_order(_root->left_child);
		    _post_order(_root->right_child);
			visit(_root->data);
		}

		//层顺遍历二叉树
		void _level_order()
		{
			if( root == NULL ){
				return;
			}
			cout<<"level order: ";
			queue<bin_tree_node<T>* > node_queue;
			node_queue.push(root);

			while( !node_queue.empty() ){
				bin_tree_node<T> *tmp = node_queue.front();
				if( tmp->left_child ){ //左孩子不为空，左孩子入队列(层序遍历，从左->右)
					node_queue.push(tmp->left_child);
				}
				if( tmp->right_child ){ //右孩子不为空，右孩子入队列 
					node_queue.push(tmp->right_child);
				}
				cout<<tmp->data<<' ';
				node_queue.pop(); //清除队列首元素
			}
			cout<<endl;
		}

		//非递归实现前中后序遍历
		//非递归前序，很好理解
		void _prev_order_nr(bin_tree_node<T> *&_root)
		{
			if(NULL == _root){
				return;
			}
			stack<bin_tree_node<T> *> s;
			s.push(_root);
			while( !s.empty() ){
				bin_tree_node<T> *tmp = s.top(); //取得栈顶元素
				cout<<tmp->data<<' ';            //访问该节点(前序)
				s.pop();                         //清理该节点
				if(tmp->right_child){    //右孩子节点先入栈
					s.push(tmp->right_child);
				}
				if(tmp->left_child){    //左孩子节点后入栈, 栈结构特点决定
					s.push(tmp->left_child);
				}
			}
			cout<<endl;
		}

		//非递归中序，较好理解
		void _in_order_nr(bin_tree_node<T> *&_root)
		{
			if(_root == NULL){
				return;
			}
			stack<bin_tree_node<T> *> s;
			bin_tree_node<T> *curr = _root;
			while(curr || !s.empty()){ //反面（curr==NULL && s.empty()）
				//1. 将当前节点的所有左孩子入栈( 模拟中序递归过程 )
				while(curr){
					s.push(curr);
					curr = curr->left_child;
				}
				//2. 当栈不为空的时候，拿出栈顶元素，最后一个左孩子节点
				if( !s.empty() ){
					bin_tree_node<T> *top = s.top();
					cout<<top->data<<' '; //访问数据
					s.pop(); //已经访问，丢弃
					curr = top->right_child; //左孩子，父节点都已经访问，开始中序右节点
				}
			}
			cout<<endl;
		}

		void _post_order_nr(bin_tree_node<T> *&_root)
		{
			bin_tree_node<T> *curr = _root;
			bin_tree_node<T> *prev = NULL;
			stack<bin_tree_node<T> *> s;
			while( curr || !s.empty() ){
				//1. 入栈所有左孩子节点
				while(curr){
					s.push(curr);
					curr = curr->left_child;
				}
				//2. 拿出栈顶元素，左孩子已经全部访问了的
				bin_tree_node<T> *top = s.top();
				//3. 只有当前节点的左右孩子都是NULL 或 左右孩子节点都已经访问过了，才能访问根节点
				if(top->right_child == NULL || top->right_child == prev){
					cout<<top->data<<' ';
					s.pop();
					prev = top;
				}else{
					curr = top->right_child;//将当前需要后序的节点，用curr指向
				}
			}
			cout<<endl;
		}

		//清除二叉树
		void _destroy(bin_tree_node<T> *&_root)
		{
			if( NULL == _root ){
				return;
			}
			_destroy(_root->left_child);
			_destroy(_root->right_child);
			delete _root;
		} 

		bin_tree_node<T> *_find(bin_tree_node<T> *_root, const T &_val)
		{
			if( NULL == _root ){
				return NULL;
			}
			if( _root->data == _val ){
				return _root;
			}
			bin_tree_node<T> *tmp = _find(_root->left_child, _val);//递归在左子树查找
			if( !tmp ){
				return _find(_root->right_child, _val); //递归在右子树查找
			}
			return NULL;
		}

		int _heigth(bin_tree_node<T> *_root)
		{
			if( NULL == _root ){
				return 0;
			}
			int curr_left_heigth = _heigth(_root->left_child) + 1;
			int curr_right_heigth = _heigth(_root->right_child) + 1;

			return curr_left_heigth > curr_right_heigth?curr_left_heigth:curr_right_heigth;
		}

		int _size(bin_tree_node<T> *_root)
		{
			if( NULL == _root ){
				return 0;
			}
			return _size(_root->left_child) + _size(_root->right_child) + 1;
		}

		//拷贝二叉树
		bin_tree_node<T>* _copy(bin_tree_node<T> *_root)
		{
			bin_tree_node<T> *new_root = NULL;
			if(_root){
				new_root = _buy_node(_root->data);
				new_root->left_child = _copy(_root->left_child);
				new_root->right_child = _copy(_root->right_child);
			}
			return new_root;
		}



	public:
		//构造函数1
		bin_tree()
			:root(NULL)
		{}

		//构造函数2
		bin_tree(T arr[], size_t size)
		{
			size_t index = 0;
			root = _create_bin_tree(arr, size, index);
		}

		//拷贝构造
		bin_tree(const bin_tree<T> &t)
		{
			this->root = _copy(t.root);
		}

		//赋值语句
		const bin_tree<T> &operator=(bin_tree<T> t)
		{
			swap(this->root, t.root);
			return (*this);
		}

		~bin_tree()
		{
			//清除数结构
			_destroy(root);
		}
		void prev_order()
		{
			cout<<"prev order: ";
			_prev_order(root); //递归
			cout<<" : ";
			_prev_order_nr(root); //非递归 
			cout<<endl;
		}

		void in_order()
		{
			cout<<"in order: ";
			_in_order(root);
			cout<<" : ";
			_in_order_nr(root);
			cout<<endl;
		}

		void post_order()
		{
			cout<<"post order: ";
			_post_order(root);
			cout<<" : ";
			_post_order_nr(root);
			cout<<endl;
		}

		void level_order()
		{
			_level_order();
		}

		int size()
		{
			return _size(this->root);
		}

		int heigth()
		{
			return _heigth(this->root);
		}

		bin_tree_node<T>* find(const T &val)
		{
			return _find(this->root, val);
		}

	public:
		bin_tree_node<T> *root; //树根 
};


