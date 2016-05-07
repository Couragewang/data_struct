#include "bin_search_tree.hpp"
int main()
{
	bs_tree<int, char> _bs;
//	_bs.insert_NR(0, 'a');
//	_bs.insert_NR(5, 'w');
//	_bs.insert_NR(6, 'r');
//	_bs.insert_NR(2, 't');
//	_bs.insert_NR(7, 'y');
//	_bs.insert_NR(8, 'u');
//	_bs.insert_NR(1, 'i');
//	_bs.insert_NR(9, 'p');

	_bs.insert_R(0, 'a');
	_bs.insert_R(5, 'w');
	_bs.insert_R(6, 'r');
	_bs.insert_R(2, 't');
	_bs.insert_R(7, 'y');
	_bs.insert_R(8, 'u');
	_bs.insert_R(1, 'i');
	_bs.insert_R(9, 'p');
	_bs.in_order();
	_bs.remove_R(5);
	_bs.in_order();
	_bs.remove_R(0);
	_bs.in_order();
	_bs.remove_R(8);
	_bs.in_order();
	_bs.remove_R(9);
	_bs.in_order();
	_bs.remove_R(1);
	_bs.in_order();
	_bs.remove_R(2);
	_bs.in_order();
	_bs.remove_R(6);
	_bs.in_order();
	return 0;
}
