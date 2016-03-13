#include <iostream>
using namespace std;

enum status{
	EMPTY = 0,  //为空，数据可以插入
	EXIST = 1,  //该位置数据存在，不可插入
	DELETED = 2,//该位置数据已经被删除
};

#ifdef _ONE_DETECT_
//一次探测
template <class k>
class hash_table{
	public:
		hash_table(const size_t &_capacity):hash_size(0), hash_capacity(_capacity)
		{
			hash_table_p = new k[_capacity];
			hash_elem_status = new status[_capacity];
			memset(hash_table_p, 0, sizeof(k)*_capacity);
			memset(hash_elem_status, EMPTY, sizeof(status) * _capacity);
		}
		~hash_table()
		{
			if(hash_table_p){
				delete []hash_table_p;
			}
			if(hash_elem_status){
				delete []hash_elem_status;
			}
		}
		bool hash_insert(const k &val)
		{
			//如果满了，并且inc_hash失败
			if( is_full() && !inc_hash() ){
				cerr<<"inc error"<<endl;
				return false;
			}
			size_t hash_key = hash(val);
			while(hash_elem_status[hash_key] == EXIST ){
				if(hash_table_p[hash_key] == val){//目标数据已经存在，不能重复插入
					return false;
				}
				++hash_key;
				if(hash_key == hash_capacity){
					hash_key = 0; //控制越界
				}
			}
			//hash_key 必定指向未被占用的位置，可以直接插入
			hash_table_p[hash_key] = val; //放入数据
			hash_elem_status[hash_key] = EXIST;
			++hash_size;
			return true;
		}
		bool hash_find(const k& val, size_t &pos/*out*/)
		{
			if(is_empty()){
				cerr<<"hash table is empty\n"<<endl;
				return false;
			}
			size_t hash_key = hash(val);
			size_t begin_key = hash_key;
			pos = 0;
			do{
				if( hash_elem_status[begin_key] == EXIST && hash_table_p[begin_key] == val){//数据存在，并且值为目标值
					pos = begin_key;
					return true;
				}
				++begin_key;
				if( begin_key == hash_capacity ){
					begin_key = 0;
				}
			}while(begin_key != hash_key && hash_elem_status[begin_key] != EMPTY);
			return false;
		}
		bool hash_remove(const k &val)
		{
			size_t pos;
			if(hash_find(val, pos)){
				hash_elem_status[pos] = DELETED;//懒删除
				--hash_size;
				return true;
			}
			return false;
		}
		void print()
		{
			for( size_t i = 0; i < hash_capacity; i++){
				cout<<"[ "<<hash_table_p[i]<<" : "<<hash_elem_status[i]<<" ]";
			}
			cout<<endl;
		}
	protected:
		//除模取余
		//线性探测
		size_t hash(const k &val)
		{
			return val%hash_capacity;
		}
		bool is_full()
		{
			if(hash_size == hash_capacity){
				return true;
			}else{
				return false;
			}
		}
		bool is_empty()
		{
			if(hash_size == 0){
				return true;
			}else{
				return false;
			}
		}
		bool inc_hash()
		{
			return true;//同学们自己完成, 作业
		}
		
	private:
		k *hash_table_p;           //hash表内存块
		status *hash_elem_status;//hash表中数据的状态
		size_t hash_size;        //hash表中元素个数
		size_t hash_capacity;     //hash表容量大小
};
#endif
#ifdef _SECOND_DETECT_
//二次探测
template <class k>
class hash_table{
	public:
		hash_table(const size_t &_capacity):hash_size(0), hash_capacity(_capacity)
		{
			cout<<"二次探测"<<endl;
			hash_table_p = new k[_capacity];
			hash_elem_status = new status[_capacity];
			memset(hash_table_p, 0, sizeof(k)*_capacity);
			memset(hash_elem_status, EMPTY, sizeof(status) * _capacity);
		}
		~hash_table()
		{
			if(hash_table_p){
				delete []hash_table_p;
			}
			if(hash_elem_status){
				delete []hash_elem_status;
			}
		}
		bool hash_insert(const k &val)
		{
			//如果满了，并且inc_hash失败
			if( is_full() && !inc_hash() ){
				cerr<<"inc error"<<endl;
				return false;
			}
			int i = 1;
			size_t hash_key = hash1(val);
			
			while(hash_elem_status[hash_key] == EXIST ){
				if(hash_table_p[hash_key] == val){//目标数据已经存在，不能重复插入
					return false;
				}
				hash_key = hash2(hash_key, i++);
				//if(hash_key == hash_capacity){
				if(hash_key >= hash_capacity){
					hash_key = 0; //控制越界
				}
			}
			//hash_key 必定指向未被占用的位置，可以直接插入
			hash_table_p[hash_key] = val; //放入数据
			hash_elem_status[hash_key] = EXIST;
			++hash_size;
			return true;
		}
		bool hash_find(const k& val, size_t &pos/*out*/)
		{
			if(is_empty()){
				cerr<<"hash table is empty\n"<<endl;
				return false;
			}
			size_t hash_key = hash1(val);
			size_t begin_key = hash_key;
			pos = 0;
			int i = 1;
			do{
				if( hash_elem_status[begin_key] == EXIST && hash_table_p[begin_key] == val){//数据存在，并且值为目标值
					pos = begin_key;
					return true;
				}
				begin_key = hash2(begin_key, i++);
				if( begin_key >= hash_capacity ){
					begin_key = 0;
				}
			}while(begin_key != hash_key && hash_elem_status[begin_key] != EMPTY);
			return false;
		}
		bool hash_remove(const k &val)
		{
			size_t pos;
			if(hash_find(val, pos)){
				hash_elem_status[pos] = DELETED;//懒删除
				--hash_size;
				return true;
			}
			return false;
		}
		void print()
		{
			for( size_t i = 0; i < hash_capacity; i++){
				cout<<"[ "<<hash_table_p[i]<<" : "<<hash_elem_status[i]<<" ]";
			}
			cout<<endl;
		}
	protected:
		//除模取余
		//线性探测
		size_t hash1(const k &val)
		{
			return val%hash_capacity;
		}
		//二次探测
		size_t hash2(const k &start, int i)
		{
			//return (start + 2*i - 1) % hash_capacity;
			return start + 2*i - 1;
		}
		bool is_full()
		{
			if(hash_size == hash_capacity){
				return true;
			}else{
				return false;
			}
		}
		bool is_empty()
		{
			if(hash_size == 0){
				return true;
			}else{
				return false;
			}
		}
		bool inc_hash()
		{
			return true;//同学们自己完成, 作业
		}
		
	private:
		k *hash_table_p;           //hash表内存块
		status *hash_elem_status;//hash表中数据的状态
		size_t hash_size;        //hash表中元素个数
		size_t hash_capacity;     //hash表容量大小
};
#endif
