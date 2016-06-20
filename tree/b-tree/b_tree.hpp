#pragma once
#include <iostream>

//动态查找树主要有：二叉查找树（Binary Search Tree），平衡二叉查找树（Balanced Binary Search Tree），红黑树(Red-Black Tree )，B-tree/B+-tree/ B*-tree (B~Tree)。前三者是典型的二叉查找树结构，其查找的时间复杂度O(log2N)与树的深度相关，那么降低树的深度自然会提高查找效率。
//但是咱们有面对这样一个实际问题：就是大规模数据存储中，实现索引查询这样一个实际背景下，树节点存储的元素数量是有限的（如果元素数量非常多的话，查找就退化成节点内部的线性查找了），这样导致二叉查找树结构由于树的深度过大而造成磁盘I/O读写过于频繁，进而导致查询效率低下（为什么会出现这种情况，待会在外部存储器-磁盘中有所解释），那么如何减少树的深度（当然是不能减少查询的数据量），一个基本的想法就是：采用多叉树结构（由于树节点元素数量是有限的，自然该节点的子树数量也就是有限的）。
//也就是说，因为磁盘的操作费时费资源，如果过于频繁的多次查找势必效率低下。那么如何提高效率，即如何避免磁盘过于频繁的多次查找呢？根据磁盘查找存取的次数往往由树的高度所决定，所以，只要我们通过某种较好的树结构减少树的结构尽量减少树的高度，那么是不是便能有效减少磁盘查找存取的次数呢？那这种有效的树结构是一种怎样的树呢？
//这样我们就提出了一个新的查找树结构——多路查找树。根据平衡二叉树的启发，自然就想到平衡多路查找树结构，也就是这篇文章所要阐述的第一个主题B~tree，即B树结构(后面，我们将看到，B树的各种操作能使B树保持较低的高度，从而达到有效避免磁盘过于频繁的查找存取操作，从而有效提高查找效率)。
//B-tree（B-tree树即B树，B即Balanced，平衡的意思）这棵神奇的树是在Rudolf Bayer, Edward M. McCreight(1970)写的一篇论文《Organization and Maintenance of Large Ordered Indices》中首次提出的（wikipedia中：http://en.wikipedia.org/wiki/B-tree，阐述了B-tree名字来源以及相关的开源地址）。

//具体讲解之前，有一点，再次强调下：B-树，即为B树。因为B树的原英文名称为B-tree，而国内很多人喜欢把B-tree译作B-树，其实，这是个非常不好的直译，很容易让人产生误解。如人们可能会以为B-树是一种树，而B树又是一种一种树。而事实上是，B-tree就是指的B树。特此说明。

//B树是为磁盘存储而专门设计的一类平衡搜索树，B树的高度仅随着它所包含的节点数按对数增长，不过因为单个节点可以包含多个关键字，所以对数的底数可以比较大，实际应用中一般是50~2000，给个直观的数字，一棵分支因子为1001、高度为2（不包含根节点）的B树，可以存储超过10亿个关键字！

//pair结构，获取查找到的节点信息，地址和索引
template<class K, class V>
struct pair{
	K key;
	V value;
	pair(const K &_key = K(), const V &_value = V())
		:key(_key)
		,value(_value)
	{}
};

//M路平衡B树, 缺省3路B树
template<class K, size_t M = 3>
struct B_tree_node{

	//subs[0]是keys[0]的左孩子， subs[1]是keys[0]的右孩子, subs[1]是keys[1]的左孩子...
	K keys[M]; //当前节点的key值集合，第M－1个位置不保存实际数据，后期分裂时方便处理
	B_tree_node<K, M> *subs[M+1]; //与key对应的节点子节点地址,第M个位置不使用，方便分裂
	size_t size;   //当前节点个数

	B_tree_node<K, M> *parent; //回指父节点
	B_tree_node()
		:size(0)
		,parent(NULL)
	{
		for(int i = 0; i < M+1; ++i){
			subs[i] = NULL;
		}
	}

};

template<class K, size_t M = 3>
class B_tree{
		typedef B_tree_node<K, M> node_t, *node_p;

		node_p _alloc_node( const K &_key )
		{
			node_p *tmp = new node_t();
			tmp->keys[0] = _key;
			tmp->size = 1;
			return tmp;
		}

		pair<node_p, int> _find( const K &_key )
		{
			node_p curr = root;
			node_p parent = NULL;
			while( curr ){
				int i = 0;
				//单节点序列按照升序排列
				while( i < curr->size && _key > curr->keys[i] ){
					i++
				}

				if( i < curr->size && _key == curr->keys[i] ){
					//find it!
					return pair<node_p, int>(curr, i);
				}

				parent = curr;
				curr = curr->subs[i];
			}

			//不存在，可以插入
			return pair<node_p, int>(parent, -1);
		}
	
	public:
		B_tree()
			:root(NULL)
		{}
		//插入成功
		bool insert( const K &_key )
		{
			//1. 当前为空树
			if( !root ){
				root = _alloc_node(_key);
				return true;
			}
			//2. 不为空树, 但需要确定当前_key是否已经存在
			pair<node_p, int> res = _find( _key );
		}

		~B_tree()
		{}
	private:
		node_p root;
};
























