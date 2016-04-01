#include "bin_tree.hpp"

int main()
{
	char tree[]="123##4##56";
	bin_tree<char> mytree(tree, strlen(tree));

	mytree.prev_order();
	return 0;
}
