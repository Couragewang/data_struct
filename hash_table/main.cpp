#include "hash_table.hpp"
#include <unistd.h>

int main()
{
	cout<<"insert begin!"<<endl;
	hash_table<int> _hash(23);
	_hash.hash_insert(1);
	sleep(1);
	_hash.print();
	_hash.hash_insert(2);
	sleep(1);
	_hash.print();
	_hash.hash_insert(3);
	sleep(1);
	_hash.print();
	_hash.hash_insert(24);
	sleep(1);
	_hash.print();
	_hash.hash_insert(25);
	sleep(1);
	_hash.print();
	_hash.hash_insert(26);
	sleep(1);
	_hash.print();

	cout<<"remove begin"<<endl;
	_hash.hash_remove(25);
	sleep(1);
	_hash.print();
	_hash.hash_remove(4);
	sleep(1);
	_hash.print();
	_hash.hash_remove(3);
	sleep(1);
	_hash.print();
	_hash.hash_remove(2);
	sleep(1);
	_hash.print();
	return 0;
}
