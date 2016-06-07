#pragma once
/// \@红黑树的五个性质：
/// \@1）每个结点要么是红的，要么是黑的。
/// \@2）根结点是黑的。
/// \@3）每个叶结点，即空结点（NIL）是黑的(注意！ 这里的叶节点不是我们度为0的节点，而是NULL指针)。
/// \@4）如果一个结点是红的，那么它的俩个儿子都是黑的(从每个叶子到根的所有路径上不能有两个连续的红色节点)。
/// \@5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。

#include <iostream>
using namespace std;
namespace RB{
	//枚举节点颜色
	enum COLOR_T{
		RED,
		BLACK,
	};

	//红黑树节点
	template<class K, class V>
	struct _rb_node{
		K key;
		V value;
		//节点颜色
		COLOR_T color;

		_rb_node<K, V> *left;
		_rb_node<K, V> *right;
		_rb_node<K, V> *parent;

		_rb_node(const K & _key = K(), const V &_value = V() )
			:key(_key)
			,value(_value)
			,color(RED) //新节点默认颜色是红色，想想为什么?
			,left(NULL)
			,right(NULL)
			,parent(NULL)
		{}
	};

	//红黑树也是搜索二叉树
	template<class K, class V>
	class rb_tree{
		typedef _rb_node<K, V> node_t, *node_p;
		public:
			rb_tree():
				root(NULL)
			{}

			~rb_tree()
			{
				_destroy(root);
			}		
		private:
			void _delete_node(node_p &_node)
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
			void _destroy(node_p &_root)
			{
				if(_root){
					_destroy(_root->left);
					_destroy(_root->right);
					_delete_node(_root);
				}
			}

			//插入新节点总是红色节点, 因为不会破坏性质 5, 尽可能维持所有性质.
			bool insert(const K &_key, const V &_value)
			{

			}

			node_p root;//红黑树树根
	};

	void auto_test()
	{
		rb_tree<int, int> tree;
	}
}





