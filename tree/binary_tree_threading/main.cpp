#include "bin_tree_thread.hpp"

int main()
{
	char arr[] = "abc###de";
	binary_tree_thread<char> thread_tree(arr, strlen(arr));

	return 0;
}
