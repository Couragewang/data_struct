#include "my_sqlist.h"

#define SQ_SIZE 5
#define INC_SIZE 3
using namespace std;

my_sqlist::my_sqlist()
{
	data_ptr = new(std::nothrow) elem_type[SQ_SIZE];
	if(NULL == data_ptr){
		std::cout<<"new error!"<<std::endl;
		exit(1);
	}
	curr_len = 0;
	total_size = SQ_SIZE;
}

my_sqlist::~my_sqlist()
{
	delete []data_ptr;
	data_ptr = NULL;
}

my_sqlist::my_sqlist(const my_sqlist &_sq_list)
{
	data_ptr = new elem_type[_sq_list.total_size];
	memcpy(data_ptr, _sq_list.data_ptr, sizeof(elem_type)*curr_len);
	curr_len = _sq_list.curr_len;
	total_size = _sq_list.total_size;
}

//?
const my_sqlist& my_sqlist::operator=(const my_sqlist &_sq_list)
{
	if(this->data_ptr){
		delete []this->data_ptr;
		this->data_ptr = NULL;
	}
	this->data_ptr = new elem_type[_sq_list.total_size];
	memcpy(this->data_ptr, _sq_list.data_ptr, sizeof(elem_type)*curr_len);
	this->curr_len = _sq_list.curr_len;
	this->total_size = _sq_list.total_size;
	return *this;
}

bool my_sqlist::inc_size()
{
	elem_type *tmp = new(std::nothrow) elem_type[total_size + INC_SIZE];
	if(NULL == tmp){
		return false;
	}
	memcpy(tmp, data_ptr, curr_len*sizeof(elem_type));
	delete []data_ptr;
	data_ptr = tmp;
	total_size += INC_SIZE;
	return true;
}

bool my_sqlist::empty()//if empty, true, else false
{
	if( curr_len == 0 ){
		return true;
	}else{
		return false;
	}
}

bool my_sqlist::full()
{
	if( curr_len == total_size ){
		return true;
	}else{
		return false;
	}
}

//modify
int my_sqlist::push_back(const_elem_type_ref val)
{
	if(full() && !inc_size()){
		return 1;//push_back error
	}
	data_ptr[curr_len++] = val;
	return 0;
}

int my_sqlist::pop_back(elem_type_ref _out_val)
{
	if( empty() ){
		return 1;//no data_ptr
	}
	_out_val = data_ptr[--curr_len];
	return 0;
}

void my_sqlist::show()
{
	int i = 0;
	for( ; i < curr_len; i++ ){
		cout<<data_ptr[i]<<' ';
	}
	cout<<":"<<curr_len<<":";
	cout<<total_size;
	cout<<endl;
}

//pos位置之前插入
int my_sqlist::insert(int pos, const_elem_type_ref _val)
{
	if(pos < 1 || (full() && !inc_size())){
		return 1;
	}


	int index = curr_len;
	while(index >= pos){
		data_ptr[index] = data_ptr[index-1];
		index--;
	}
	data_ptr[index] = _val;
	curr_len++;
	return 0;
}

int my_sqlist::erase(int pos)
{
	if( pos < 1 || pos > curr_len ){
		return 1;
	}

	int start_index = pos;
	while(start_index < curr_len){
		data_ptr[start_index-1] = data_ptr[start_index];
		start_index++;
	}
	curr_len--;
	return 0;
}

int my_sqlist::clear()
{
	delete []data_ptr;
	data_ptr = NULL;
	curr_len = 0;
	return 0;
}

//capacity
int my_sqlist::size()
{
	return curr_len;
}

int my_sqlist::capacity()
{
	return total_size;

}

//element access
const_elem_type_ref my_sqlist::at(int pos)
{
	if( pos>=1 && pos<=curr_len ){
		return data_ptr[pos];
	}
}

const_elem_type_ref my_sqlist::front()
{
	if(curr_len > 0){
		return data_ptr[0];
	}
}

const_elem_type_ref my_sqlist::back()
{
	if(curr_len>0){
		return data_ptr[curr_len-1];
	}
}

elem_type_ptr my_sqlist::data()
{
	return data_ptr;
}

