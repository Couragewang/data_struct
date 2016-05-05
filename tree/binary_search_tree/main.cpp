#include "bin_search_tree.hpp"
int main()
{
	bs_tree<int, char> _bs;
	_bs.insert_NR(0, 'a');
	_bs.insert_NR(5, 'w');
	_bs.insert_NR(6, 'r');
	_bs.insert_NR(2, 't');
	_bs.insert_NR(7, 'y');
	_bs.insert_NR(8, 'u');
	_bs.insert_NR(1, 'i');
	_bs.insert_NR(9, 'p');

	_bs.in_order();
	return 0;
}
