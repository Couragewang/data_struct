#pragma once

#include <iostream>

// 可以证明：在n个结点的二叉链表中含有n+1个空指针。因为含n个结点的二叉链表中含有2n个指针，除了根结点，
// 每个结点都有一个从父结点指向该结点的指针，因此一共使用了n-1个指针，所以在n个结点的二叉链表中含有2n-(n-1)=n+1个空指针。
// 因此，可以利用这些空指针，存放指向结点在某种遍历次序下的前驱和后继结点的指针。这种附加的指针称为线索，
// 加上了线索的二叉链表称为线索链表，相应的二叉树称为线索二叉树。为了区分一个结点的指针是指向其孩子的指针，
// 还是指向其前驱或后继结点的线索，可在每个结点中增加两个线索标志。

using namespace std;

enum pointer_tag{
	THREAD,
	LINK,
};

template<class T>
struct binary_tree_thread_node{
	T data;
	binary_tree_thread_node<T> *left_child;
	binary_tree_thread_node<T> *right_child;
	binary_tree_thread_node<T> *father; //后序遍历？
	pointer_tag left_tag;
	pointer_tag right_tag;

	binary_tree_thread_node(T x)
		:data(x)
		 ,left_child(NULL)
		 ,right_child(NULL)
		 ,left_tag(LINK)
		 ,right_tag(LINK)
	{}
};

template<class T>
class binary_tree_thread{
	public:
		binary_tree_thread()
			:root(NULL)
		{}
		binary_tree_thread(T array[], size_t size)
		{
			int index = 0;
			_create_tree(root, array, size, index);
		}

		void in_threading()
		{
			binary_tree_thread_node<T> *prev = NULL;
			_in_threading(root, prev);
		}

		void prev_threading()
		{
			binary_tree_thread_node<T> *prev = NULL;
			_prev_threading(root, prev);
		}

		void post_threading()
		{
			binary_tree_thread_node<T> *prev = NULL;
			_post_threading(root, prev);
		}

		void in_order()
		{
			cout<<"in order : ";
			_in_order(root);
			cout<<endl;
		}

		void prev_order()
		{
			cout<<"prev order : ";
			_prev_order(root);
			cout<<endl;
		}


		~binary_tree_thread()
		{}
	private:
		binary_tree_thread_node<T> *buy_node(T val)
		{
			binary_tree_thread_node<T> *tmp = new binary_tree_thread_node<T>(val);
			return tmp;
		}

		void _create_tree(binary_tree_thread_node<T> *&root, T array[], size_t size, int &index)
		{
			if(index < size && array[index] != '#'){
		    	root = buy_node(array[index]);
		    	_create_tree(root->left_child, array, size, ++index);
		    	_create_tree(root->right_child, array, size, ++index);
				if(root->left_child){
					root->left_child->father = root;
				}
				if(root->right_child){
					root->left_child->father = root;
				}
			}
		}

		//中序线索化 : 线索化的过程，是需要查找节点的前驱和后继的，而在二叉树中，找节点的前驱后继，需要在遍历中做到
		void _in_threading(binary_tree_thread_node<T> *curr, binary_tree_thread_node<T> *&prev)
		{
			if(curr){
				_in_threading(curr->left_child, prev);
				//站在当前节点的角度, prev作为前驱节点，如果可以，被当前节点的左子树指向
				if( curr->left_child == NULL ){
					curr->left_tag = THREAD;
					curr->left_child = prev;
				}
				//站在前驱节点的角度，curr是prev的后继
				if( prev && prev->right_child == NULL ){
					prev->right_tag = THREAD;
					prev->right_child = curr; //右孩子指向后继节点
				}
				prev = curr;
				_in_threading(curr->right_child, prev);
			}
		}

		//前序线索化
		void _prev_threading(binary_tree_thread_node<T> *curr, binary_tree_thread_node<T> *&prev)
		{
			if( curr ){
				//1. 站在当前节点的角度, prev作为前驱节点，如果可以，被当前节点的左子树指向
				if( curr->left_child == NULL ){
					curr->left_tag = THREAD;
					curr->left_child = prev;
				}
				//2. 站在前驱节点的角度，curr是prev的后继
				if(prev && prev->right_child == NULL){
					prev->right_tag = THREAD;
					prev->right_child = curr;
				}

				prev = curr;

				//3. 只有当前节点left或right是LINK, 才需要递归线索化
				if( curr->left_tag == LINK ){
					_prev_threading(curr->left_child, prev);
				}

				//4. 同上
				if( curr->right_tag == LINK ){
					_prev_threading(curr->right_child, prev);
				}
			}
		}
		//后序线索化
		void _post_threading(binary_tree_thread_node<T> *curr, binary_tree_thread_node<T> *&prev)
		{
			if( curr ){
				if( curr->left_tag  == LINK ){
					//左孩子是数据节点
					_post_threading( curr->left_child, prev );
				}
				if( curr->right_tag == LINK ){
					_post_threading( curr->right_child, prev );
				}
				if( curr->left_child == NULL ){
					curr->left_tag = THREAD;
					curr->left_child = prev;
				}
				if(prev && prev->right_child == NULL){
					prev->right_tag = THREAD;
					prev->right_child = curr;
				}
				prev = curr;
			}
		}

		//前序遍历 : 中 －》 左 －》 右
		void _prev_order(binary_tree_thread_node<T> *curr)
		{
			while(curr){
				while(curr){
					cout<<curr->data<<" "; //1. 只要不为空，就直接访问该节点
					if( curr->left_tag == THREAD){ //2. 如果后序节点是索引，在访问该节点之后，直接跳出
						break;
					}
					curr = curr->left_child;//3. 否则直接指向左子树
				}
				curr = curr->right_child; //4. 只要到了这一步，cur直接指向其后继节点
			}
		//	while(curr){
		//		while(curr && curr->left_tag == LINK){//1. 先找到最左节点，为第一个要访问的节点
		//			cout<<curr->data<<" "; //2. 访问他
		//			curr = curr->left_child;
		//		}
		//		cout<<curr->data<<" ";
		//		while(curr->right_tag == THREAD && curr->right_child){ //3. 当前节点的后继节点（中序遍历的后继节点）, 考虑单左分支情况，和左子树为满二叉的情况
		//			curr = curr->right_child;
		//			cout<<curr->data<<" ";
		//		}
		//		//4. 左分支访问完毕，访问右分支
		//		curr = curr->right_child;
		//	}
		}

		//中序遍历: 左 －》 中 －》 右 
		//与中序线索化相对应
		void _in_order(binary_tree_thread_node<T> *curr)
		{
			while(curr){
				while(curr && curr->left_tag == LINK){//1. 先找到最左节点，为第一个要访问的节点
					curr = curr->left_child;
				}
				cout<<curr->data<<" "; //2. 访问他
				while(curr->right_tag == THREAD && curr->right_child){ //3. 当前节点的后继节点（中序遍历的后继节点）, 考虑单左分支情况，和左子树为满二叉的情况
					curr = curr->right_child;
					cout<<curr->data<<" ";
				}
				//4. 左分支访问完毕，访问右分支
				curr = curr->right_child;
			}
		}

		//后序遍历
		void _post_order()
		{

		}
	private:
		binary_tree_thread_node<T> *root;
};











