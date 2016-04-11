#include "bin_tree.hpp"

int main()
{
	char tree[]="123##4##56";
	cout<<"++++++++++++++基本++++++++++++++"<<endl;
	bin_tree<char> mytree(tree, strlen(tree));
	mytree.prev_order();
	mytree.in_order();
	mytree.post_order();
	mytree.level_order();
	cout<<"size: "<<mytree.size()<<endl;
	cout<<"heigth: "<<mytree.heigth()<<endl;

	cout<<"++++++++++++++拷贝++++++++++++++"<<endl;
	bin_tree<char> copy_tree(mytree);
	copy_tree.prev_order();
	copy_tree.in_order();
	copy_tree.post_order();
	cout<<"size: "<<copy_tree.size()<<endl;
	cout<<"heigth: "<<copy_tree.heigth()<<endl;

	cout<<"++++++++++++++赋值++++++++++++++"<<endl;
	bin_tree<char> _copy_tree;
	_copy_tree = mytree;
	_copy_tree.prev_order();
	_copy_tree.in_order();
	_copy_tree.post_order();
	cout<<"size: "<<_copy_tree.size()<<endl;
	cout<<"heigth: "<<_copy_tree.heigth()<<endl;

	bin_tree_p<char> mytree_p(tree, strlen(tree));
	return 0;
}
