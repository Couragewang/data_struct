#pragma once

/// \@红黑树的五个性质：
/// \@1）每个结点要么是红的，要么是黑的。
/// \@2）根结点是黑的。
/// \@3）每个叶结点，即空结点（NIL）是黑的(注意！ 这里的叶节点不是我们度为0的节点，而是NULL指针)。
/// \@4）如果一个结点是红的，那么它的俩个儿子都是黑的(从每个叶子到根的所有路径上不能有两个连续的红色节点)。
/// \@5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。

//第3条，显然这里的叶子节点不是平常我们所说的叶子节点，如图标有NIL的为叶子节点，为什么不按常规出牌，因为按一般的叶子节点也行，但会使算法更复杂
//第4条，即该树上决不允许存在两个连续的红节点；
//所有性质1-5合起来约束了该树的平衡性能--即该树上的最长路径不可能会大于2倍最短路径。为什么？
//因为第1条该树上的节点非红即黑，由于第4条该树上不允许存在两个连续的红节点，那么对于从一个节点到其叶子节点的一条最长的路径一定是红黑交错的，那么最短路径一定是纯黑色的节点；而又第5条从任一节点到其叶子节点的所有路径上都包含相同数目的黑节点，这么来说最长路径上的黑节点的数目和最短路径上的黑节点的数目相等！而又第2条根结点为黑、第3条叶子节点是黑，那么可知：最长路径<=2*最短路径。一颗二叉树的平衡性能越好，那么它的效率越高！显然红黑树的平衡性能比AVL的略差些，但是经过大量试验证明，实际上红黑树的效率还是很不错了，仍能达到O(logN)，这个我不知道，我现在不可能做过大量试验，只是听人家这样说，O(∩_∩)O哈哈~但你至少知道他的时间复杂度一定小于2O(logN)!

#include <iostream>
#include <stdlib.h>
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

		_rb_node(const K & _key = K(), const V &_value = V(), const COLOR_T &_color = RED )
			:key(_key)
			,value(_value)
			,color(_color) //新节点默认颜色是红色，想想为什么?
			,left(NULL)
			,right(NULL)
			,parent(NULL)
		{}
	};

	//红黑树也是搜索二叉树
	template<class K, class V>
	class rb_tree{
		typedef _rb_node<K, V> node_t, *node_p;
		private:
			void _rotate_left(node_p &rotate_node, node_p &_root)//左旋
			{
				node_p _sub_right = rotate_node->right;
				node_p _sub_right_left = _sub_right->left;
				rotate_node->right = _sub_right_left;
				if( _sub_right_left ){
					_sub_right_left->parent = rotate_node;
				}

				_sub_right->left = rotate_node;

				if( rotate_node == _root ){ //当前的轴心旋转节点是根节点
					_root = _sub_right;
				}else if( rotate_node->parent->left == rotate_node ){ //否则当前节点不是根节点, 之前必定有其他节点,轴心旋转节点是它的父节点的左孩子
					rotate_node->parent->left = _sub_right;
				}else{
					rotate_node->parent->right = _sub_right;
				}
				_sub_right->parent = rotate_node->parent;
				rotate_node->parent = _sub_right;
			}

			void _rotate_right(node_p &rotate_node, node_p &_root) //右旋
			{
				node_p _sub_left = rotate_node->left;
				node_p _sub_left_right = _sub_left->right;
				rotate_node->left = _sub_left_right;
				if( _sub_left_right ){
					_sub_left_right->parent = rotate_node;
				}
				_sub_left->right = rotate_node;
				if( rotate_node == _root ){
					_root = _sub_left;
				}else if( rotate_node->parent->left == rotate_node ){
					rotate_node->parent->left = _sub_left;
				}else{
					rotate_node->parent->right = _sub_left;
				}

				_sub_left->parent = rotate_node->parent;
				rotate_node->parent = _sub_left;
			}

			void _in_order( node_p &_root)
			{
				if( _root ){
					_in_order( _root->left );
					cout<<_root->key<<" ";
					_in_order( _root->right );
				}
			}

			int _height( node_p &_root)
			{
				if( _root ){
					int _left = _height(_root->left) + 1;
					int _right = _height(_root->right) + 1;
					return _left > _right?_left:_right;
				}
			}

			bool _is_blance(node_p &_root)
			{
				if(!_root){
					return false;
				}

				int _left = _height(_root->left);
				int _right = _height(_root->right);

				if( _left > _right && _left > 2 * _right ){//左子树高于右子树两倍以上
					return false;
				}
				if( _left < _right && _left * 2 < _right ){//右子树高于左子树两倍以上
					return false;
				}

				return true;
			}
		public:
			rb_tree():
				root(NULL)
			{}

			~rb_tree()
			{
				_destroy(root);
				root = NULL;
			}

			//插入新节点总是红色节点, 因为不会破坏性质 5, 尽可能维持所有性质.
			bool insert(const K &_key, const V &_value)
			{
				return _insert(root, _key, _value);
			}

			void in_order()
			{
				cout<<"in order: ";
				_in_order(root);
				cout<<endl;
			}

			bool is_blance()
			{
				return _is_blance(root);
			}

			void destroy()
			{
				_destroy(root);
				root = NULL;
			}

		private:
			void _delete_node(node_p &_node)
			{
				if( _node ){
					delete _node;
					_node = NULL;
				}
			}

			node_p alloc_node(const K &_key, const V &_value, const COLOR_T &_color)
			{
				node_p tmp = new node_t(_key, _value, _color);
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

			//红黑树照样也是平衡二叉树
			bool _insert(node_p &_root, const K &_key, const V &_value)
			{
				if( !_root ){
					_root = alloc_node(_key, _value, BLACK);
					return true;
				}
				node_p curr = _root;
				node_p parent = curr;
				while(curr){
					if( curr->key > _key ){ //新插入节点，左子树
						parent = curr;
						curr = curr->left;
					}else if( curr->key < _key ){//新插入节点，右子树
						parent = curr;
						curr = curr->right;
					}else{ //有重复元素，直接返回
						return false;
					}
				}
			    //parent 指向当前节点的插入位置的父节点
			    curr = alloc_node(_key, _value, RED);
			    if( parent->key > _key ){
			    	//插入左子树
			    	parent->left = curr;
			    	curr->parent = parent;
			    }else{
			    	//插入右子树
			    	parent->right = curr;
			    	curr->parent = parent;
			    }

				//插入完毕，接下来进行调整, 红黑树是近似平衡二叉树，所以有些情况并不需要调整
				//关于插入，待插入节点颜色必须是红色，因为如果是黑色， 会导致规则5不合法
				//而如果插入的节点的父节点是红色，而当前节点的颜色也是红色，导致规则4不合法
				//换句话说，如果待插入节点的父节点是黑色，则不需要调整!!!
				while( curr != _root && parent->color == RED ){
					node_p grandfather = parent->parent;//肯定不为空，因为parent->color是红色，说明肯定不是根节点（根节点是黑色）
					if( parent == grandfather->left ){ //父节点是祖父节点的左孩子
						node_p uncle = grandfather->right; //叔叔节点
						if( uncle && uncle->color == RED ){ //情况1. parent和uncle都是红色的（grandfather肯定是黑色的), 逐次向上进行颜色变换。
							parent->color = BLACK;
							uncle->color = BLACK;
							grandfather->color = RED;
							curr = grandfather;
							parent = curr->parent;
						}else{//当插入节点的uncle节点不存在或者是黑色，要进行旋转 
							if(curr == parent->right){//左右
								//转换成左左
								_rotate_left(parent, _root); //左旋
								parent = curr;
							}

							grandfather->color = RED;
							parent->color = BLACK;
							_rotate_right(grandfather, _root);
						}
					}else{//父节点是祖父节点的左孩子
						node_p uncle = grandfather->left; //叔叔节点 
						if( uncle && uncle->color == RED ){//同情况1
							uncle->color = BLACK;
							parent->color = BLACK;
							grandfather->color = RED;
							curr = grandfather;
							parent = curr->parent;
						}else{//当插入节点的uncle节点不存在或者是黑色，要进行旋转
							if( curr == parent->left ){ //右左
								//转化成右右
								_rotate_right(parent, _root);
								parent = curr;
							}
							grandfather->color = RED;
							parent->color = BLACK;
							_rotate_left(grandfather, _root);
						}
					}
				}
				_root->color = BLACK;
				return true;
			}

		private:
			node_p root;//红黑树树根
	};

	void auto_test()
	{
		rb_tree<int, int> tree;
		int a[] = {2,3,4,1,23,13,34,45,556,67,6};
	//	int a[] = {2,3,4,1};//,23,13,34,45,556,67,6};
		int len;
		len = sizeof(a)/sizeof(a[0]);
		int i = 0;
		for(; i < len; i++){
			tree.insert(a[i], a[i]);
		}
		tree.in_order();
		cout<<"is blance : "<<tree.is_blance()<<endl;

		//test is blance
		srand(time(0));
		rb_tree<int, int> tree1;

		for( i = 0; i < 10000; i++ ){
			tree1.insert(rand()%1000, i);
			if( i%100 == 0 ){
				cout<<"/////////////////////////////////////////////////////////////////"<<endl;
				tree1.in_order();
				cout<<"is blance : "<<tree1.is_blance()<<endl;
				tree1.destroy();
			}
		}
		srand(time(0));
		rb_tree<int, int> tree2;

		for( i = 0; i < 10000; i++ ){
			tree2.insert(rand()%10000, i);
			if( i%100 == 0 ){
				cout<<"/////////////////////////////////////////////////////////////////"<<endl;
				tree2.in_order();
				cout<<"is blance : "<<tree2.is_blance()<<endl;
			}
		}
	}
}








