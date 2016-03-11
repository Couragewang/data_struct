#include <iostream>

//C++版本的链表，以练习为目的，该版本不带头节点,实现基本实现
//相关面试题，学生自行实现(参照C版本实现)
typedef int elem_type;

typedef struct node{
	elem_type data;
	struct node *next;
}node_t, *node_ptr, **node_pptr;

class mylist{
	private:
		node_ptr head;//链表头部
		node_ptr buy_node(elem_type _data);
        void list_init();
		int  delete_node(node_ptr _n);
	public:
		mylist();
		~mylist();
        int is_empty();
        int push_front(elem_type _val);
        int pop_front();
        int push_back(elem_type _val);
        int pop_back();
        int clear();
        int insert(node_ptr pos, elem_type _val);//节点之后插入
        int size();
        int get_elem(int i, elem_type *_val);
        int find(elem_type _val, node_pptr _node/*output*/);
        int erase(node_ptr _erase_node);
        int remove_val(elem_type _val);
        void show_list();
};
