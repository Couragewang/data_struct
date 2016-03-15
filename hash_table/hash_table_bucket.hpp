#pragma once
//采用开散列的方式解决hash冲突

#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace bucket{
	template <class k, class v>
	struct hash_table_node{
		k key;
		v val;
		hash_table_node<k, v> *next;

		hash_table_node(const k &_key, const v &_val)
			:key(_key)
			 ,val(_val)
			 ,next(NULL)
		{}
	};

	const int prime_size = 28;
	static const unsigned long prime_list[prime_size] = 
	{
		53ul,         97ul,         193ul,       389ul,       769ul,
		1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
		49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
		1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
		50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
		1610612741ul, 3221225473ul, 4294967291ul
	};

	//模版函数, 仿函数, 重载operator()
	template<class k>
	struct __hash_func{
		size_t operator()(const k &_key){
			return _key;
		}
	};
	//特化string类型
	//如若要支持其他类型，可以偏特化对应的类型
	template<>
	struct __hash_func<string>{
		static size_t KDRHash(const char *str)
		{
			unsigned int seed = 131;
			unsigned int hash = 0;
			while(*str){
				hash = hash * seed + (*str++);
			}
			return (hash & 0x7FFFFFFF);
		}
		size_t operator()(const string &s){
			return KDRHash(s.c_str());
		}
	};

    template <class k, class v, template<class> class hash_func = __hash_func>
    class hash_table{
    	private:
			typedef struct hash_table_node<k, v> node;
			typedef struct hash_table_node<k, v>* node_p;

			//查找最小的大于size的素数，作为hash表的大小
			size_t get_prime_num(size_t size)
			{
				size_t pos = 0;
				while( pos < prime_size ){
					if( prime_list[pos] > size ){
						break;
					}
					++pos;
				}
				return prime_list[pos];
			}

			node_p buy_node(const k &_key, const v &_value)
			{
				return new node(_key, _value);
			}
			void delete_node(const node *&_n)
			{
				if(_n){
					delete _n;
				}
			}
			size_t _hash_func( const k &_key, size_t _size)
			{
				//计算key, 保证不能越界
				//此处使用仿函数，让程序的扩展性更强
				//对特定的hash函数定制特化函数，灵活
				return  hash_func<k>()(_key) % _size;
			}
			bool check_capacity(size_t _size)
			{
				if(size < hash_table_bucket.size()){//负载因子 < 1
					return false;
				}

				// 如果size大于table的大小，则进行重建，重新负载节点
				size_t new_capacity = get_prime_num(size);
				vector<node_p> tmp_table;
				tmp_table.reserve(new_capacity);
				tmp_table.assign(new_capacity, 0);
				size_t old_capacity = hash_table_bucket.size();

				//所有节点重新映射
				for(size_t i = 0; i < old_capacity; i++){
					node_p begin = hash_table_bucket[i];
					while(begin){
						//拿下当前节点
						node_p tmp = begin->next;
						begin = begin->next;
						//重新计算hash值
						size_t index = _hash_func(tmp->key, new_capacity);
						//头插
						tmp->next = tmp_table[index];
						tmp_table[index] = tmp;
					}
				}
				//交换内容，释放老的数据
				hash_table_bucket.swap(tmp_table);
				return true;
			}
    	public:
    		hash_table()
				:size(0)
			{}
			bool hash_insert(const k &_key, const v &_value)
			{
				check_capacity(hash_table_bucket.size());//插入前先检测是否需要重新归置hash桶，检测负载因子，此处为1,实际节点个数 == 桶节点个数
				size_t index =  _hash_func(_key, hash_table_bucket.size());
				//先确定是目标节点是否存在
				node_p begin = hash_table_bucket[index];//指向特定桶首部, 开始查找
				while(begin){
					if(begin->key == _key){
						return false;
					}
					begin = begin->next;
				}
				size++; //节点个数递增 
				//查找一次，目标节点不存在，可以插入，选择头插法
				node_p tmp  = buy_node(_key, _value);
				tmp->next = hash_table_bucket[index];//指向特定桶首部
				hash_table_bucket[index] = tmp;
			}
			const node_p hash_find(const k &_key)
			{
				size_t index = _hash_func(_key, hash_table_bucket.size());
				node_p begin = hash_table_bucket[index];
				while(begin){
					if(begin->key == _key){
						return begin;
					}
					begin = begin->next;
				}
				return NULL;
			}
			bool hash_remove(const k &_key)
			{
				size_t index = _hash_func(_key, hash_table_bucket.size());
				node_p begin = hash_table_bucket[index];
				if( NULL == begin ){
					return false;
				}
				//欲删节点就是第一个节点，直接删除
				if( begin->key == _key ){
					hash_table_bucket[index] = begin->next;
					delete_node(begin);
					size--;
					return true;
				}
				//目标节点在散列表中, 先查找目标节点
				node_p prev = begin;
				begin = begin->next;
				while(begin){
					if(begin->key == _key){//找到该节点 
						prev->next = begin->next;
						delete_node(begin);
						size--;
						return true;
					}
					prev = begin;
					begin = begin->next;
				}
				return false;
			}
			void print()
			{
				cout<<"capacity : "<<hash_table_bucket.size()<<", node size : "<<size<<endl;
				for(size_t i = 0; i < hash_table_bucket.size(); i++){
					node_p begin = hash_table_bucket[i];
					while(begin){
						cout<<"{ "<<begin->key<<" : "<<begin->value<<" },";
						begin = begin->next;
					}
					cout<<"{ NULL, NULL}"<<endl;
				}
			}
    		~hash_table()
			{}

		private:
    		vector<node_p> hash_table_bucket;//hash桶, 它本身的size代表桶的数目，不等于实际node节点的个数
			size_t size;                    //实际node的个数
    };
}








