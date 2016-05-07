#pragma once

#include <iostream>
//二叉查找树
//(1)左子树不空，则左子树上的所有结点的值均小于根结点的值
//(2)右子树不空，则右子树上的所有结点的值均大于根结点的值
//二叉查找树可以为空，二叉查找树是递归定义的，也就是说其左右子树也为二叉查找树。
//二叉查找树是一种动态查找表，可以进行动态地插入和删除。前面的定义中我们假定二叉查找树不含有相同元素。
//由定义可知二叉查找树的中序序列为一个递增序列

template<class T>
void swap(T &val1, T &val2)
{
	T tmp = val1;
	val1 = val2;
	val2 = tmp;
}

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

	void delete_node(node_p del)
	{
		if( del ){
			delete del;
		}
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

	//从搜索二叉树中移除节点
	//搜索二叉树不能随便进行删除，输出节点之后，还要保证满足搜索二叉的特性。
	//所以删除搜索二叉树节点有三种情况
	//1. 欲删除的节点是叶子节点，没有左右子树，这种情况最简单，直接删除节点
	//2. 欲删除的节点非叶子节点，但只有左子树或者右子树。
	//3. 欲删除的节点非叶子节点，并且包含有左子树和右子树
	bool _remove_NR(node_p &_root, const K &_key)
	{
		if( NULL == _root ){
			return false;
		}
		node_p parent = NULL;
		node_p del = _root;
		//a.找到欲删除的节点
		while( del ){
			if( _key < del->key ){
				parent = del;
				del = del->left;
			}else if( _key > del->key ){
				parent = del;
				del = del->right;
			}else{
				break;
			}
		}

		//b. 找到了才需要删除
		if( del ){
			//三种情况
			//1. 欲删除的节点是叶子节点，没有左右子树，这种情况最简单，直接删除节点
			if( NULL == del->left && NULL == del->right ){
				if(parent->left == del){
					parent->left = NULL;
				}else{
					parent->right = NULL;
				}
				delete_node(del);
				return true;
			}
			//2. 欲删除的节点非叶子节点，但只有左子树或者右子树。
			if( del->left == NULL ){ //只有右子树, 单分之，用右子树填补，依旧保证有序。
				if( del != _root ){ //考虑欲删除节点是否是root，root没有parent
					if( parent->left == del ){//欲删除节点是父节点的左孩子
						parent->left = del->right;
					}else{
						parent->right = del->right;
					}
				}else{//是root节点
					_root = del->right;
				}
			}else if( del->right == NULL ){//只有左子树, 单分之，用左子树填补，依旧保证有序。
				if( del != _root ){
					if( parent->left == del ){
						parent->left = del->left;
					}else{
						parent->right = del->left;
					}
				}else{
					_root = del->left;
				}
			}else{ //左右子树皆不为空
				//3. 欲删除的节点非叶子节点，并且包含有左子树和右子树
				//找到右子树中的最左节点（比del节点大的所有节点中，最小的节点）
				node_p first_inorder = del->right;
				parent = del;
				while(first_inorder->left){
					parent = first_inorder;
					first_inorder = first_inorder->left;
				}
				//交换del节点和最左节点的内容
				swap(del->key, first_inorder->key);
				swap(del->val, first_inorder->val);

				//欲删除节点变成了first_inorder节点！并且该节点要么为叶子，要么为只有右分支节点
				if(parent->left == first_inorder){
					parent->left = first_inorder->right;
				}else{
					parent->right = first_inorder->right;
				}
				del = first_inorder;
			}
			delete_node(del);
		}else{
			return false;
		}
		return true;
	}
	bool _remove_R(node_p &_root, const K &_key)
	{
		if( _root ){
			if( _key < _root->key ){
				return _remove_R(_root->left, _key); //键值小于root key, 在左子树中删除
			}else if(_key > _root->key){
				return _remove_R(_root->right, _key);
			}else{ //找到对应的节点, 进行删除
				node_p del = NULL;
			    //1. 欲删除的节点是叶子节点，没有左右子树，这种情况最简单，直接删除节点
				//2. 如果左or右子树为空，则用一个子树进行填补。
				//3. 如果左右均不为空，则使用右子树中序的第一个节点填补
				if( _root->left == NULL ){
					del = _root;
					_root = _root->right;
					delete_node(del);
				}else if( _root->right == NULL ){
					del = _root;
					_root = _root->left;
					delete_node(del);
				}else{
					node_p right_first = _root->right;
					//查找_root中序的最左节点,或查找右子树的中序遍历的第一个节点
					while(right_first->left){
						right_first = right_first->left;
					}
					swap(_root->val, right_first->val);
					swap(_root->key, right_first->key);
					_remove_R(_root->right, right_first->key);
				}
				return true;
			}
		}
		return false;
	}

	void _destroy(node_p &_root)
	{
		if( _root ){
			_destroy( _root->left );
			_destroy( _root->right );
			delete _root;
			_root = NULL;
		}
	}
public:
	bs_tree()
		:root(NULL)
	{}
	~bs_tree()
	{
		_destroy(root);
	}
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
	//删除节点
	bool remove_NR(const K &_key)
	{
		return _remove_NR(root, _key);
	}
	//递归删除节点
	bool remove_R(const K &_key)
	{
		return _remove_R(root, _key);
	}
private:
	node_p root;
};

