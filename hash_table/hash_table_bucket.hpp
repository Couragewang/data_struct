#pragma once
//采用开散列的方式解决hash冲突

#include <iostream>
#include <string>
using namespace std;
namespace bucket{
	template <class k, class v>
	struct hash_table_node{
		k key;
		v val;
		hash_table_node<k, v> *next;

		hash_table_node(const k &_key, const v &_val)
			:key(_keya)
			 ,val(_val)
			 ,next(NULL)
		{}
	};

	//模版函数, 仿函数, 重载operator()
	template<class k>
	struct __hash_func{
		size_t operator(const k &_key){
			return _key;
		}
	};
	template<>
	struct __hash_func<string>{

	};

    template <class k>
    class hash_table{
    	public:
    		hash_table(size_t capacity)
			{}
    		~hash_table()
			{}
    	private:
    		k *hash_table_bucket;//hash桶
    
    };

}
