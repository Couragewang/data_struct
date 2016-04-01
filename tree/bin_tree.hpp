// \@实现二叉树的基本操作
#pragma once

#include <iostream>
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

		//前序遍历二叉树
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
			_prev_order(root);
			cout<<endl;
		}

		void in_order()
		{
			cout<<"in order: ";
			_in_order(root);
			cout<<endl;
		}

		void post_order()
		{
			cout<<"post order: ";
			_post_order(root);
			cout<<endl;
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











