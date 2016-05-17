#pragma once
#include <iostream>

// 平衡二叉树（Balanced Binary Tree）是二叉查找树的一个进化体，也是第一个引入平衡概念的二叉树。
// 1962年，G.M. Adelson-Velsky 和 E.M. Landis发明了这棵树，所以它又叫AVL树。平衡二叉树要求对于
// 每一个节点来说，它的左右子树的高度之差不能超过1，如果插入或者删除一个节点使得高度之差大于1，
// 就要进行节点之间的旋转，将二叉树重新维持在一个平衡状态。这个方案很好的解决了二叉查找树退化
// 成链表的问题，把插入，查找，删除的时间复杂度最好情况和最坏情况都维持在O(logN)。但是频繁旋
// 转会使插入和删除牺牲掉O(logN)左右的时间，不过相对二叉查找树来说，时间上稳定了很多。

//思考：1. 平衡二叉树，首先是搜索二叉树
//      2. 同样的一组有序序列，理论上可以构建出不同的搜索二叉树（只要满足搜索二叉树的概念即可）
//      3. 在一个搜索二叉树中，每个子树满足搜索二叉树的定义, 所以理论上，无论你对子树如何调整，只要
//      4. 该子树依旧满足搜索二叉树的概念，则该树整体不受影响
//      5. 平衡二叉树就是根据上面的概念，来避免搜索二叉树退化问题

template <class K, class V>
struct AVL_node{
	K key;   //节点键值
	V value; //节点内容

	//连接信息
	AVL_node<K, V> *left;
	AVL_node<K, V> *right;
	AVL_node<K, V> *parent;

	//平衡因子
	ssize_t bf;

	//构造函数
	AVL_node(const K &_key, const V &_value)
		:key(_key)
		,value(_value)
		,left(NULL)
		,right(NULL)
		,parent(NULL)
	{}
};

template<class K, class V>
class AVL_tree{
	typedef AVL_node<K, V> node_t, *node_p, &node_ref;

	void delete_node(node_p &_node)
	{
		if( _node ){
			delete _node;
			_node = NULL;
		}
	}

	node_p alloc_node(const K &_key, const V &_value)
	{
		node_p tmp = new node_t(_key, _value);
		return tmp;
	}

	void _delete_tree(node_p &_root)
	{
		if( _root ){
	        _delete_tree( _root->left );
	        _delete_tree( _root->right );
			if( _root->left == NULL && _root->right == NULL ){
				delete_node(_root);
			}
		}
	}

	bool isempty()
	{
		return root == NULL;
	}

public:
	AVL_tree()
		:root(NULL)
	{}

	//在AVL中插入节点
	bool insert(const K &_key, const V &_value)
	{
		//1. 当前是一棵空树
		if( isempty() ){
			root = alloc_node(_key, _value);
			return true;
		}

		//2. 在搜索二叉树当中进行插入，需要先确认插入位置
		node_p curr = root;
		node_p parent = curr;
		//通过curr游标，便利搜索二叉树
		while( curr ){
			if( _key < curr->key ){
				parent = curr;
				curr = curr->left;  //curr指向左孩子
			}else if( _key > curr->key ){
				parent = curr;
				curr = curr->right;
			}else{ //节点内容相等，搜索二叉树中，不允许有相同key节点存在
				return false; //直接返回错误，无法插入
			}
		}
		//3. 只要能走到这里，说明肯定已经找到对应的插入的位置了，这里需要强调一下，搜索二叉树的插入位置，肯定是在叶子节点处
		//开始插入
		node_p tmp = alloc_node( _key, _value );
		if( parent && tmp->_key < parent->key ){//待插入节点key小于当前节点
			parent->left = tmp; //插入左子树
		}else{
			parent->right = tmp; //插入左子树
		}

		//4. 确定是否平衡与旋转
	}
	~AVL_tree()
	{
		_delete_tree( root );
	}

private:
	node_p root; //AVL树根节点
};






