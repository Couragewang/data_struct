#pragma once

#include <iostream>
//二叉查找树
//(1)左子树不空，则左子树上的所有结点的值均小于根结点的值
//(2)右子树不空，则右子树上的所有结点的值均大于根结点的值
//二叉查找树可以为空，二叉查找树是递归定义的，也就是说其左右子树也为二叉查找树。
//二叉查找树是一种动态查找表，可以进行动态地插入和删除。前面的定义中我们假定二叉查找树不含有相同元素。
//由定义可知二叉查找树的中序序列为一个递增序列

template<class K, class V>
struct bst_node{
	K key;
	V val;
	bst_node *left;
	bst_node *right;
	bst_node(const K &_key, const V &_val)
		:key(_key)
		,val(_val)
		,left(NULL)
		,right(NULL)
	{}
};

template<class K, class V>
class bs_tree{
private:
	typedef bst_node<K, V> node_t, *node_p;

	node_p buy_node(const K &_key, const V &_val)
	{
		node_p tmp = new node_t(_key, _val);
		return tmp;
	}

	//递归插入
	bool _insert_R(node_p &_root, const K &_key, const V &_val)
	{
		if(NULL == _root){
			_root = buy_node(_key, _val);
			return true;
		}else{
			if(_key < _root->key){//带插节点key小于当前节点值,插入当前节点左侧
				return _insert_R(_root->left, _key, _val);
			}else if( _key > _root->key){
				return _insert_R(_root->right, _key, _val);
			}else{
				return false;
			}
		}
	}
	//非递归插入，搜索二叉插入，总能插入到一个叶子节点后面
	bool _insert_NR(node_p &_root, const K &_key, const V &_val)
	{
		node_p curr = _root;
		node_p prev = NULL;
		if(NULL == _root){
			_root = buy_node(_key, _val);
			return true;
		}
		while(curr){
			if( _key < curr->key ){   //键值小于当前节点,左子树
				prev = curr;          //保存当前有效节点
				curr = curr->left;    //进入左子树
			}else if( _key > curr->key){ //键值大于当前节点,右子树
				prev = curr;          //保存当前有效节点
				curr = curr->right;
			}else{
				return false; //搜索二叉没有相同key的节点
			}
		}
		//curr定然为空，prev指向最后一个有效节点，当前节点插入prev的left或right
		if( _key > prev->key){ //右子树
			prev->right = buy_node(_key, _val);
		}else if( _key < prev->key){//左子树
			prev->left = buy_node(_key, _val);
		}else{
			return false;
		}
		return true;
	}
	//递归查找 
	node_p _find_R(const node_p &_root, const K &_key)
	{
		if(_root){
			if( _key < _root->key ){//key值小于当前的值，在左子树进行查找
				return _find_R(_root->left, _key);
			}else if( _key > _root->key ){//key值大于当前的值，在右子树进行查找 
				return _find_R(_root->right, _key);
			}else{
				return _root;
			}
		}
		//查找到_root为空，必定没有找到
		return NULL;
	}
	//非递归查找
	node_p _find_NR(const node_p &_root, const K &_key)
	{
		node_p curr = _root;
		while( curr ){
			if( _key < curr->key ){
				curr = curr->left;
			}else if( _key > curr->key ){
				curr = curr->right;
			}else{
				return curr;
			}
		}
		return NULL;
	}

	//中序遍历是一个有序序列, 左－》中－》右
	void _in_order(const node_p &_root)
	{
		if( _root ){
			_in_order(_root->left);
			std::cout<<"[ "<<_root->key<<":"<<" '"<<_root->val<<" '"<<" ] ";
			_in_order(_root->right);
		}
	}
public:
	bs_tree()
		:root(NULL)
	{}
	~bs_tree()
	{}
	bs_tree(const bs_tree &tmp);
	bs_tree& operator=(const bs_tree &tmp);
public:
	bool insert_R(const K &_key, const V &_val)
	{
		return _insert_R(root, _key, _val);
	}
	bool insert_NR(const K &_key, const V &_val)
	{
		return _insert_NR(root, _key, _val);
	}
	node_p find_R(const K &_key)
	{
		return _find_R(root, _key);
	}
	node_p find_NR(const K &_key)
	{
		return _find_NR(root, _key);
	}
	void in_order()
	{
		_in_order(root);
		std::cout<<std::endl;
	}

private:
	node_p root;
};







