#pragma once
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

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

using namespace std;

namespace non_recursion{

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
    	AVL_node(const K &_key = K(), const V &_value = V())
    		:key(_key)
    		,value(_value)
    		,bf(0)
    		,left(NULL)
    		,right(NULL)
    		,parent(NULL)
    	{}
    };
    
    template<class K, class V>
    class AVL_tree{
    	typedef AVL_node<K, V> node_t, *node_p, **node_pp,&node_ref;
    
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
    	
    	void _in_order( node_p &_root )
    	{
    		if( _root == NULL ){
    			return;
    		}
    		_in_order(_root->left);
    		cout<<_root->key<<" ";
    		_in_order(_root->right);
    	}
    
    	void _pre_order( node_p &_root )
    	{
    		if( _root == NULL ){
    			return;
    		}
    		cout<<_root->key<<" ";
    		_pre_order(_root->left);
    		_pre_order(_root->right);
    	}
    
    	void _post_order( node_p &_root )
    	{
    		if( _root == NULL ){
    			return;
    		}
    		_post_order(_root->left);
    		_post_order(_root->right);
    		cout<<_root->key<<" ";
    	}
    
    	int _height(node_p &_root)
    	{
    		if( _root == NULL ){
    			return 0;
    		}
    
    		int _left = _height(_root->left) + 1;
    		int _right = _height(_root->right) + 1;
    
    		return _left > _right?_left:_right;
    	}
    
    	bool _is_blance(node_p &_root){
    		if(_root == NULL){
    			return 0;
    		}
    
    		int _left = _height( _root->left );
    		int _right = _height( _root->right );
    		if( abs(_left - _right) != abs(_root->bf) ){ //左右子树高度不等于根节点的平衡因子,有问题
    			cerr<<"平衡因子不合理： "<<abs(_left-_right)<<" : "<<abs(_root->bf)<<endl;
    			return false;
    		}
    		return abs(_root->bf) <= 1;
    	}
    
    	//右旋
    	void _rotate_R(node_p &_node) //注意引用绝不能少
    	{
    #ifdef _DEBUG_
    		cout<<"right rotate"<<endl;
    #endif
    		node_p _node_left = _node->left; 
    		node_p _node_left_right = _node_left->right;
    
    		_node->left = _node_left_right;
    		if(_node_left_right){
    			_node_left_right->parent = _node;
    		}
    		//提升左节点
    		_node_left->right = _node;
    		_node_left->parent = _node->parent;
    		_node->parent = _node_left; //考虑_node节点的父节点为空的情况
    
    		_node->bf = _node_left->bf = 0;
    		_node = _node_left;//更新新的父指针 ,curr指针不变
    	}
    	
    	//左旋
    	void _rotate_L(node_p &parent) //注意引用不能少
    	{
    #ifdef _DEBUG_
    		cout<<"left rotate"<<endl;
    #endif
    		node_p _sub_right = parent->right;
    		node_p _sub_right_left = _sub_right->left;
    		parent->right = _sub_right_left;
    		if(_sub_right_left){
    			_sub_right_left->parent = parent;
    		}
    		_sub_right->left = parent;
    		_sub_right->parent = parent->parent;
    		parent->parent = _sub_right;
    
    		parent->bf = _sub_right->bf = 0;
    		parent = _sub_right; //更新新的父指针 ,curr指针不变
    	}
    	
    	//先左旋后右旋
    	void _rotate_LR(node_p &parent)
    	{
    #ifdef _DEBUG_
    		cout<<"left right rotate"<<endl;
    #endif
    		//1. 先完成左旋
    		node_p _sub_left = parent->left;
    		node_p _sub_left_right = _sub_left->right;
    		node_p _sub_lr_left = _sub_left_right->left; //该子树是要被_sub_left接管的
    		_sub_left->right = _sub_lr_left;
    		if( _sub_lr_left ){
    			_sub_lr_left->parent = _sub_left;
    		}
    		_sub_left_right->left = _sub_left;
    		_sub_left->parent = _sub_left_right;
    		//2. 完成左旋之后，更新_sub_left的平衡因子
    		//   强调一下，对于_node_left_right节点的平衡因子，可以暂时不用调整，因为最终他的平衡因子会是0
    		if(_sub_left_right->bf == -1/*该节点的左子树高*/ || _sub_left_right->bf == 0 /*该节点左右子树等高*/){
    			//新增节点在_sub_left_right的左子树
    			_sub_left->bf = 0; //_sub_left(当前平衡因子是1)接管了_sub_left_right的左子树，并且新节点在_sub_left_right的左子树,接管之后，_sub_left的右子树少了一层
    		}else if( _sub_left_right->bf == 1 /*该节点的右子树高*/){
    			_sub_left->bf = -1; //同上
    		}else{
    			cerr<<"平衡因子异常"<<endl;
    		}
    		//2. 右旋
    		node_p _new_sub_left = _sub_left_right;
    		node_p _new_sub_left_right = _new_sub_left->right;
    		parent->left = _new_sub_left_right;
    		if( _new_sub_left_right ){
    			_new_sub_left_right->parent = parent;
    		}
    
    		_new_sub_left->right = parent;
    		_new_sub_left->parent = parent->parent;//注意parent->parent当作左值和右值的区别
    		parent->parent = _new_sub_left;
    
    		if(_new_sub_left->bf == 0 || _new_sub_left->bf == 1/*当时新增节点在该节点的右子树*/){
    			parent->bf = 0;
    		}else if(_new_sub_left->bf == -1){
    			parent->bf = 1;
    		}else{
    			cerr<<"平衡因子异常"<<endl;
    		}
    		_new_sub_left->bf = 0;
    		parent = _new_sub_left;//更新外层指针
    	}
    
    	//先右旋后左旋
    	void _rotate_RL(node_p &parent)
    	{
    #ifdef _DEBUG_
    		cout<<"right left rotate"<<endl;
    #endif
    		node_p _sub_right = parent->right;
    		node_p _sub_right_left = _sub_right->left;
    		node_p _sub_rl_right = _sub_right_left->right;
    		//1. 先右旋
    		_sub_right->left = _sub_rl_right;
    		if(_sub_rl_right){
    			_sub_rl_right->parent = _sub_right;
    		}
    		_sub_right_left->right = _sub_right;
    		_sub_right->parent = _sub_right_left; 
    		//2. 旋转完成之后，更新_sub_right的平衡因子
    		//   3种情况
    		//平衡二叉：左右子树，要么相等，要么差一个节点
    		if( _sub_right_left->bf == 0/*只有3个节点的情况*/ || _sub_right_left->bf == 1){
    			_sub_right->bf = 0;
    		}else if( _sub_right_left->bf == -1 ){
    			_sub_right->bf = 1;
    		}else{
    			cerr<<"平衡因子异常"<<endl;
    		}
    
    		//3. 左旋
    		node_p _sub_rl_left = _sub_right_left->left;
    		parent->right = _sub_rl_left;
    		if(_sub_rl_left){
    			_sub_rl_left->parent = parent;
    		}
    		_sub_right_left->left = parent;
    		_sub_right_left->parent = parent->parent;
    		parent->parent = _sub_right_left;
    
    		//4. 更新平衡因子，有一个节点已经更新
    		if(_sub_right_left->bf == 0 || _sub_right_left->bf == -1){
    			parent->bf = 0;
    		}else if( _sub_right_left->bf == 1 ){
    			parent->bf = -1;
    		}else{
    			cerr<<"平衡因子异常"<<endl;
    		}
    
    		//5. 更新平衡因子
    		_sub_right_left->bf = 0; 
    		parent = _sub_right_left; //更新上层parent指针
    	}
    
    public:
    	AVL_tree()
    		:root(NULL)
    	{}
    
    	//在AVL中插入节点
    	bool insert(const K &_key, const V &_value)
    	{
    #ifdef _DEBUG_
    		cout<<"before  insert: "<<_key<<" inorder : ";
    		_in_order(root);
    		cout<<endl;
    #endif
    
    		//1. 当前是一棵空树
    		if( isempty() ){
    			root = alloc_node(_key, _value);
    			return true;
    		}
    
    		//2. 在搜索二叉树当中进行插入，需要先确认插入位置
    		node_p curr = root;
    		node_p parent = curr;
    		//通过curr游标，遍历搜索二叉树
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
    		if( parent && tmp->key < parent->key ){//待插入节点key小于当前节点
    			parent->left = tmp; //插入左子树
    			tmp->parent = parent;
    		}else{
    			parent->right = tmp; //插入左子树
    			tmp->parent = parent;
    		}
    
    		//4. 确定是否平衡与旋转
    		bool is_rotate = false;
    		curr = tmp;
    		while( parent ){
    			if(parent->left == curr){//新增节点在当前节点左子树
    				--parent->bf; //新节点插入到了当前父节点的左子树部分
    			}else{
    				++parent->bf; //新节点插入到了当前父节点的右子树部分
    			}
    			//自低向上进行统计
    			//平衡因子本质其实是当前父节点的左右子树的高度差
    			//a. 插入新节点之后，当前父节点左右子树高度差为0,不需要调整
    			if( parent->bf == 0 ){
    				break;
    			}else if( parent->bf == -1 /*左子树深1*/ || parent->bf == 1 /*右子树深1*/ ){
    				//需要继续往上查找
    				curr = parent;
    				parent = curr->parent;
    			}else{ //否则需要进行旋转
    				is_rotate = true;
    				if( parent->bf == -2 ){ //左
    					if( curr->bf == -1 ){ //左左, 右旋
    						_rotate_R(parent); //此处注意，判断出来parent节点的左右子树不平衡，需要调整，但调整过程，对上层不影响
    					}else{ //左右
    						_rotate_LR(parent);
    					}
    				}else{ //右
    					if( curr->bf == 1 ){ //右右, 左旋
    						_rotate_L(parent);
    					}else{ //右左
    						_rotate_RL(parent);
    					}
    				}
    				break;
    			}
    		}
    
    		if(is_rotate){
    			node_p pp_node = parent->parent; //parent指向旋转后的新子树根节点，并且该新节点的parent已经在旋转的时候得到更新, 此处直接使用即可
    			if( pp_node == NULL ){
    				root = parent;
    			}else{
    				if(pp_node->key > parent->key){ //父节点key大, 注意看看，此时，谁是父节点！！！
    					pp_node->left = parent;
    				}else{
    					pp_node->right = parent;
    				}
    			}
    		}
    #ifdef _DEBUG_
    	cout<<"after insert: "<<_key<<" inorder : ";
    	_in_order(root);
    	cout<<endl;
    #endif
    		return true;
    	}
    
    	node_p find(const K &_key)
    	{
    		node_p curr = root;
    
    		while(curr){
    			if( curr->key > _key ){
    				curr = curr->left;
    			}else if( curr->key < _key ){
    				curr = curr->right;
    			}else{
    				return curr;
    			}
    		}
    
    		return NULL;
    	}
    
    	void in_order()
    	{
    		cout<<"in order: ";
    		_in_order(root);
    		cout<<endl;
    	}
    
    	void pre_order()
    	{
    		cout<<"pre order: ";
    		_pre_order( root );
    		cout<<endl;
    	}
    
    	void post_order()
    	{
    		cout<<"post order: ";
    		_post_order( root );
    		cout<<endl;
    	}
    
    	bool is_blance()
    	{
    		return _is_blance( root );
    	}
    
    	int height()
    	{
    		return _height( root );
    	}
    
    	bool remove(const K &_key)
    	{
    		//交给同学们自己完成, 选做一下
    		return true;
    	}
    
    	~AVL_tree()
    	{
    		_delete_tree( root );
    	}
    
    private:
    	node_p root; //AVL树根节点
    };

}//end namespace

//递归版本
namespace recursion{
	template<class K, class V>
	struct AVL_node{
		//key, value
		K key;
		V value;
		//左右子树, 此处其实不需要parent
		AVL_node<K, V> *left;
		AVL_node<K, V> *right;
		//平衡因子
		ssize_t bf;

		AVL_node(const K &_key = K(), const V &_value=V()):
			key(_key)
			,value(_value)
			,left(NULL)
			,right(NULL)
			,bf(0)
		{}
	};

	template< class K, class V >
	class AVL_tree{
			typedef AVL_node<K, V> node_t, *node_p, **node_pp;

			//左旋 -> 右右
			void _rotate_L(node_p &parent)
			{
				node_p _sub_right = parent->right;
				node_p _sub_right_left = _sub_right->left;
				parent->right = _sub_right_left;
				_sub_right->left = parent;
				parent->bf = _sub_right->bf = 0;
				parent = _sub_right;
			}

			//左右旋 -> 左右
			void _rotate_LR(node_p &parent)
			{
				//左旋转
				node_p _sub_left = parent->left;
				node_p _sub_left_right = _sub_left->right;
				node_p _sub_lr_left = _sub_left_right->left;
				_sub_left->right = _sub_lr_left;
				_sub_left_right->left = _sub_left;
				//更新_sub_left的平衡因子
				 if(_sub_left_right->bf == 1){ //插入到了_sub_left_right节点的右子树
					 _sub_left->bf = -1;
				 }else{
					 _sub_left->bf = 0;
				 }

				 //右旋
				 node_p _sub_lr_right = _sub_left_right->right;
				 parent->left = _sub_lr_right;
				 _sub_left_right->right = parent;
				 //更新parent的平衡因子
				 if(_sub_left_right->bf == 1 || _sub_left_right->bf == 0){
					 parent->bf = 0;
				 }else{
					 parent->bf = 1;
				 }
				 _sub_left_right->bf = 0;
				 parent = _sub_left_right; //更新指向调整子树的指针
			}
			//右旋 -> 左左
			void _rotate_R(node_p &parent)
			{
				//旋转 
				node_p _sub_left = parent->left;
				node_p _sub_left_right = _sub_left->right;
				parent->left = _sub_left_right;
				_sub_left->right = parent;
				//更新平衡因子
				parent->bf = _sub_left->bf = 0;
				parent = _sub_left;
			}
			//右左旋 -> 右左
			void _rotate_RL(node_p &parent)
			{
				node_p _sub_right = parent->right;
				node_p _sub_right_left = _sub_right->left;
				node_p _sub_rl_right = _sub_right_left->right;

				//先右旋
				_sub_right->left = _sub_rl_right;
				_sub_right_left->right = _sub_right;
				//更新_sub_right的平衡因子
				if( _sub_right_left->bf == 1 || _sub_right_left->bf == 0){
					_sub_right->bf = 0;
				}else{
					_sub_right->bf = 1;
				}
				
				//左旋
				node_p _sub_rl_left = _sub_right_left->left;
				parent->right = _sub_rl_left;
				_sub_right_left->left= parent;
				//更新平衡因子
				if( _sub_right_left->bf == 1 ){
					parent->bf = -1;
				}else{
					parent->bf = 0;
				}

				_sub_right_left->bf = 0;
				parent = _sub_right_left;
			}

			void _in_order(node_p &_root)
			{
				if(_root){
					_in_order(_root->left);
					cout<<_root->key<<" ";
					_in_order(_root->right);
				}
			}
		
			ssize_t _height(node_p &_root)
			{
				if(_root == NULL){
					return 0;
				}

				ssize_t _left = _height(_root->left) + 1;
				ssize_t _right = _height(_root->right) + 1;
				return _left > _right?_left:_right;
			}

			int _is_blance(node_p &_root)
			{
				if( !_root ){
					return 0;
				}
				ssize_t _left = _height(_root->left);
				ssize_t _right = _height(_root->right);
				if( abs(_left - _right) != abs(_root->bf) ){
					cerr<<"平衡因子不合理： "<<abs(_left-_right)<<" : "<<abs(_root->bf)<<endl;
					return 0;
				}

				return abs(_root->bf) <= 1;
			}

    	    node_p alloc_node(const K &_key, const V &_value)
    	    {
    	    	node_p tmp = new node_t(_key, _value);
    	    	return tmp;
    	    }

		public:
			AVL_tree():
				root(NULL)
			{}

			bool _insert(node_p &_root, const K &_key,const V &_value, bool &is_rotate)
			{
				bool ret = false;
				if( _root == NULL ){
					_root = alloc_node(_key, _value);
					ret = true;
				}else if( _root->key > _key ){//插入节点在当前节点左子树
					ret = _insert(_root->left, _key, _value, is_rotate);
					if( !is_rotate ){ //当前并没有被旋转,从左分支返回上来的
						_root->bf--;  //左高度累加
					}
					//累加完毕之后，判断是否需要旋转平衡
					if( _root->bf == -2 ){
						if( _root->left->bf == -1 ){ //左左
							_rotate_R(_root);
						}else{ //左右
							_rotate_LR(_root);
						}
						is_rotate = true;
					}
				}else if( _root->key < _key ){//插入节点在当前节点右子树
					ret = _insert(_root->right, _key, _value, is_rotate);
					if( !is_rotate ){//当前并没有被旋转,从右分支返回上来的
						_root->bf++;//右高度累加
					}
					//累加完毕之后，判断是否需要旋转平衡
					if( _root->bf == 2 ){
						if( _root->right->bf == 1 ){ //右右
							_rotate_L(_root);
						}else{ //右左
							_rotate_RL(_root);
						}
						is_rotate = true;
					}
				}else{
					ret = false; //插入失败
					is_rotate = true; //直接返回,不做累加
				}
				return ret;
			}

			bool is_empty()
			{
				return root == NULL;
			}

			bool insert(const K &_key, const V &_value)
			{
				bool is_rotate = false;
				return _insert(root, _key, _value, is_rotate);
			}

			void in_order()
			{
				cout<<"in order: ";
				_in_order(root);
				cout<<endl;
			}

			ssize_t height()
			{
				return _height(root);
			}

			int is_blance()
			{
				return _is_blance(root);
			}

			~AVL_tree()
			{}
		private:
			node_p root; //树根
	};
    int test_avl()
    {
		cout<<"test"<<endl;
        AVL_tree<int, int> t1;
    	int a1[] = {3, 2, 1};
 //     int a1[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
        for (int  i = 0; i < sizeof(a1)/sizeof(int); ++i)
        {
    		t1.insert(a1[i], a1[i]);
        }
        
        t1.in_order();
    
        AVL_tree<int, int> t2;
        int a2[] = {164, 34, 7, 112, 92, 26, 18, 143, 152, 9, 21, 3, 123};
    
        for (int  i = 0; i < sizeof(a2)/sizeof(int); ++i)
        {
    		t2.insert(a2[i], a2[i]);
        }
        
        t2.in_order();
        
        AVL_tree<int, int> t3;
    	int a3[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
        for (int  i = 0; i < sizeof(a3)/sizeof(int); ++i)
        {
    		t3.insert(a3[i], a3[i]);
        }
        
        t3.in_order();
        
        cout<<"t1是否平衡?:"<<t1.is_blance()<<endl;
        cout<<"t2是否平衡?:"<<t2.is_blance()<<endl;
        cout<<"t3是否平衡?:"<<t3.is_blance()<<endl;
    
        return 0;
    }
}

