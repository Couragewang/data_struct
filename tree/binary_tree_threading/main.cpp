#include "bin_tree_thread.hpp"

int main()
{
	char arr[] = "abc###de";
	//char arr[]="123##4##56";
	binary_tree_thread<char> thread_tree(arr, strlen(arr));
	thread_tree.prev_threading();
	thread_tree.prev_order();

	binary_tree_thread<char> thread_tree2(arr, strlen(arr));
	thread_tree2.in_threading();
	thread_tree2.in_order();

//	thread_tree.prev_threading();
//	thread_tree.prev_order();
	binary_tree_thread<char> thread_tree1(arr, strlen(arr));
	thread_tree1.post_threading();
	thread_tree1.post_order();
	return 0;
}
