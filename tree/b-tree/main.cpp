#include "b_tree.hpp"

using namespace std;

int main()
{

	B_tree<int, 5> tree; //key->int, M -> 5
	int a[] = {53, 75, 139, 49, 145, 36, 101};
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i){
		tree.insert(a[i]);
	}
	tree.in_order();
	return 0;
}
