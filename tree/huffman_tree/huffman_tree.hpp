#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>  //构建堆的算法

//给定n个权值作为n的叶子结点，构造一棵二叉树，若带权路径长度达到最小，
//称这样的二叉树为最优二叉树，也称为哈夫曼树(Huffman Tree)。
//哈夫曼树是带权路径长度最短的树，权值较大的结点离根较近。

//二叉结构
#ifdef _BINARY_
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

#elif _STATIC_
//静态结构
typedef unsigned int index_t;

template<class T>
struct huffman_node{
	T weight;
	index_t parent; //父节点索引
	index_t left;   //左孩子索引
	index_t right;  //右孩子索引
	index_t index;  //本节点的索引

	huffman_node(const T &_weight)
		:weight(_weight)
		,parent(-1)
		,left(-1)
		,right(-1)
		,index(-1)
	{}
};

template<class T>
class huffman_tree{
	typedef huffman_node<T> node_t, *node_p, &node_ref; 
	//构建最小堆算法需要
	static bool cmp(node_p _node1, node_p _node2)
	{
		return _node1->weight > _node2->weight;
	}
public:
	huffman_tree()
		:root(-1)
	{}
	~huffman_tree()
	{}
	void create_huffman_tree(const T *array, size_t size)
	{
		if( NULL == array || size <= 0){
			return;
		}
		std::vector<node_p> min_heap;
		//给静态存储结构和最小堆都预留出2*size-1个节点
		//因为huffman树中只有度为0（叶子节点）和 度为2（非叶子节点，都由叶子节点或其他节点生成）的节点，所以总节点个数就是2*size-1
		huffman_nodes.reserve(2*size-1);
		min_heap.reserve(2*size-1);//stl当中堆结构有算法提供支持, 并没有对应的堆容器
		index_t i = 0;

		for( ; i < size; ++i ){
			huffman_nodes.push_back(node_t(array[i])); //插入当前节点到huffman中
			node_ref node = huffman_nodes.back(); //更新节点索引
			node.index = i;
			min_heap.push_back(&node);
		}

		//结合stl算法，构建最小堆
		make_heap(min_heap.begin(), min_heap.end(), cmp);

		 while(min_heap.size() > 1){
			 node_p node_first = min_heap[0]; //最小节点地址
			 //在堆中，去掉最小节点的地址
			 pop_heap(min_heap.begin(), min_heap.end(), cmp);
			 min_heap.pop_back();

			 node_p node_second = min_heap[0]; //次小节点地址
			 //在堆中，去掉次小节点的地址
			 pop_heap(min_heap.begin(), min_heap.end(), cmp);
			 min_heap.pop_back();

#ifdef _DEBUG_
			std::cout<<node_first->weight<<std::endl;
			std::cout<<node_second->weight<<std::endl;
			std::cout<<"############################"<<std::endl;
#endif

			 huffman_nodes.push_back(node_t(node_first->weight + node_second->weight)); //插入新节点
			 node_ref parent = huffman_nodes.back();
			 parent.index = i++; //继续更新索引

			 parent.left = node_first->index;
			 parent.right = node_second->index;
			 node_first->parent = parent.index;
			 node_second->parent = parent.index;

			 //更新堆中数据
			 min_heap.push_back(&parent);
			 make_heap(min_heap.begin(), min_heap.end(), cmp);
		 }
		 root = min_heap[0]->index;
	}

	void level_order()
	{
		std::queue<index_t> q;
		if( root != -1 ){
			q.push(root);
		}

		while(!q.empty()){
			index_t index = q.front();
			std::cout<<huffman_nodes[index].weight<<" ";
			if(huffman_nodes[index].left != -1){
				q.push(huffman_nodes[index].left);
			}
			if(huffman_nodes[index].right != -1){
				q.push(huffman_nodes[index].right);
			}
			q.pop();
		}
		std::cout<<std::endl;
	}
private:
	std::vector<node_t> huffman_nodes; //保存所有huffman节点
	index_t root;                      // 静态huffman树的根节点
};
#endif


