#include "hash_table_bucket.hpp"
#include <unistd.h>

int main()
{
	cout<<"insert begin!"<<endl;
	bucket::hash_table<int, string, bucket::__hash_func> _hash;//使用缺省的hash函数
	_hash.hash_insert(1, "value1");
	_hash.print();
	sleep(2);
	_hash.hash_insert(2, "value2");
	_hash.print();
	sleep(2);
	_hash.hash_insert(3, "value3");
	_hash.print();
	sleep(2);
	_hash.hash_insert(4, "value4");
	_hash.print();
	sleep(2);
	_hash.hash_insert(5, "value5");
	_hash.print();
	sleep(2);
	cout<<"begin remove"<<endl;
	_hash.hash_remove(3);
	_hash.print();

	bucket::hash_table_node<int, string>* p = _hash.hash_find(4);
	cout<<"find it !, val is : "<<p->val<<endl;

	//测试hash string
//	bucket::hash_table<string, string> _hash;//使用缺省的hash函数
//	_hash.hash_insert("key1", "value1");
//	_hash.print();
//	sleep(2);
//	_hash.hash_insert("key2", "value2");
//	_hash.print();
//	sleep(1);
//	_hash.hash_insert("key3", "value3");
//	_hash.print();
//	sleep(1);
//	_hash.hash_insert("key4", "value4");
//	_hash.print();
//	sleep(1);
//	_hash.hash_insert("key2", "value2");
//	_hash.print();
//	sleep(1);
//	_hash.hash_insert("key6", "value6");
//	_hash.print();
//	sleep(1);


//	_hash.hash_insert(1);
//	sleep(1);
//	_hash.print();
//	_hash.hash_insert(2);
//	sleep(1);
//	_hash.print();
//	_hash.hash_insert(3);
//	sleep(1);
//	_hash.print();
//	_hash.hash_insert(24);
//	sleep(1);
//	_hash.print();
//	_hash.hash_insert(22);
//	sleep(1);
//	_hash.print();
//	_hash.hash_insert(26);
//	sleep(1);
//	_hash.print();
//
//	cout<<"remove begin"<<endl;
//	_hash.hash_remove(22);
//	sleep(1);
//	_hash.print();
//	_hash.hash_remove(4);
//	sleep(1);
//	_hash.print();
//	_hash.hash_remove(3);
//	sleep(1);
//	_hash.print();
//	_hash.hash_remove(2);
//	sleep(1);
//	_hash.print();
	return 0;
}
