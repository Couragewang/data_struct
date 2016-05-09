#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>  //构建堆的算法

//给定n个权值作为n的叶子结点，构造一棵二叉树，若带权路径长度达到最小，
//称这样的二叉树为最优二叉树，也称为哈夫曼树(Huffman Tree)。
//哈夫曼树是带权路径长度最短的树，权值较大的结点离根较近。

template<class T>
struct huffman_node{
	T weight; //权重
	huffman_node *parent; //父孩子节点
	huffman_node *left;   //左孩子节点
	huffman_node *right;  //右孩子节点

	huffman_node(const T &_weight)
		:parent(NULL)
		,left(NULL)
		,right(NULL)
		,weight(_weight)
	{}
};

template<class T>
class huffman_tree{
	typedef huffman_node<T> *huffman_node_p, huffman_node_t;
	typedef huffman_node<T> &huffman_node_ref, *&huffman_node_pref;

	void delete_node(huffman_node_pref _node)
	{
		if( _node ){
			delete _node;
			_node = NULL;
		}
	}

	huffman_node_p alloc_node(const T &_val)
	{
		huffman_node_p node = new huffman_node_t(_val);
		return node;
	}
	//哈夫曼树也是二叉,采用后序清除
	void _destroy(huffman_node_pref _root)
	{
		if( _root ){
			_destroy(_root->left); //清除左孩子
			_destroy(_root->right);//清除右孩子
			delete_node(_root);
		}
	}

	//static bool cmp(std::vector<huffman_node<T>* >::iterator _iter1, std::vector<huffman_node<T>* >::iterator _iter2)
	//static bool cmp(huffman_node_p node1, huffman_node_p node2)
	static bool cmp(huffman_node_p node1, huffman_node_p node2)
	{
		return node1->weight > node2->weight;
	}

public:
	huffman_tree()
		:root(NULL)
	{}

	void create_huffman_tree(const T *array, size_t size, const T &invalid)
	{
		std::vector<huffman_node_p> min_heap;
		int i = 0;
		for( ; i < size; i++ ){
			if(array[i] != invalid){
				huffman_node_p node = alloc_node(array[i]);
				min_heap.push_back(node);
			}
		}
		//判断是否有元素
		if( min_heap.empty() ){
			return;
		}
		//构建最小堆
		make_heap(min_heap.begin(), min_heap.end(), cmp);

		huffman_node_p parent = min_heap[0];
		while(min_heap.size() > 1){ //堆中元素只要有2个（包括两个）以上
			huffman_node_p min_first = min_heap[0];//0号下标min
			//清除当前最小节点
			pop_heap(min_heap.begin(), min_heap.end(), cmp); 
			min_heap.pop_back();
#ifdef _DEBUG_
		for( i=0 ; i < min_heap.size(); i++){
			std::cout<<min_heap[i]->weight<<" ";
		}
		std::cout<<std::endl;
#endif

			huffman_node_p min_second  = min_heap[0];
			//清除当前最次小节点
			pop_heap(min_heap.begin(), min_heap.end(), cmp); 
			min_heap.pop_back();

			parent = alloc_node(min_first->weight + min_second->weight);
			parent->left = min_first;
			parent->right = min_second;
			min_first->parent = parent;
			min_second->parent = parent;

			//添加新的节点
			min_heap.push_back(parent);
			make_heap(min_heap.begin(), min_heap.end(), cmp);
		}
		root = parent;
	}

	void level_order()
	{
		std::queue<huffman_node_p> q;
		if( root ){
			q.push(root);
		}
		while(!q.empty()){
			huffman_node_p node = q.front(); //得到队列头部
			std::cout<<node->weight<<" ";
			if( node->left ){
				q.push(node->left);
			}
			if( node->right ){
				q.push(node->right);
			}
			q.pop();
		}
		std::cout<<std::endl;
	}

	~huffman_tree()
	{
		_destroy(root);
	}
private:
	huffman_node_p root;
};




