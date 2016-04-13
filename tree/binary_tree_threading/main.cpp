#include "bin_tree_thread.hpp"

int main()
{
	char arr[] = "abc###de";
	//char arr[]="123##4##56";
	binary_tree_thread<char> thread_tree(arr, strlen(arr));
	thread_tree.in_threading();
	thread_tree.in_order();
	return 0;
}
