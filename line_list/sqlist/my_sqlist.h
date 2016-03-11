#ifndef _MY_SQLIST_
#define _MY_SQLIST_

#include <iostream>
typedef int  elem_type;
typedef int &elem_type_ref;
typedef const int &const_elem_type_ref;
typedef int *elem_type_ptr;

class my_sqlist{
	public:
		my_sqlist();
		~my_sqlist();

		my_sqlist(const my_sqlist &_sq_list);
		const my_sqlist &operator = (const my_sqlist &_sq_list);

		//modify
		int push_back(const_elem_type_ref val);
		int pop_back(elem_type_ref _out_val);
		int insert(int pos, const_elem_type_ref data);
		int erase(int pos);
		int clear();

		//capacity
		int size();
		int capacity();
		bool empty();//if empty, true, else false
		bool full();
		bool inc_size();
		
		//element access
		const_elem_type_ref at(int pos);
		const_elem_type_ref front();
		const_elem_type_ref back();
		elem_type_ptr data();
		
		//show data
		void show();
	private:
		elem_type *data_ptr; //data buffer
		int curr_len;         //current len
		int total_size;        //total size
};

#endif
