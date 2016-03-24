#include "heap.hpp"

int main()
{
	//int arr[] = {3,2,4,5,5,6,74,6,47,36,52,4,3,12};
	int arr[] = {10,9,8,7,6,5,4,3,2,1,0};
	int size = sizeof(arr)/sizeof(arr[0]);
	show(arr, size);
	make_min_heap(arr, size);
	show(arr, size);

	int out = -1;
	min_heap_delete(arr, size, out);
	show(arr, size);
	std::cout<<"delete: "<<out<<std::endl;


	min_heap_add(arr, size-1, -1);
	show(arr, size);

	head_sort(arr, size);
	show(arr, size);
	return 0;
}
