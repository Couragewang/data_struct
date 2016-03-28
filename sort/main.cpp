#include "sort.hpp"

int main()
{
	int arr[10];
	cout<<"Please Enter: ";
	fflush(stdout);
	for(int i = 0; i < 10; i++){
		cin>>arr[i];
	}
	//bubble_sort(arr,10);
	//insert_sort(arr, 10);
	//shell_sort(arr, 10);
	//select_sort(arr, 10);
	//select_sort_op(arr, 10);
	//quick_sort(arr, 0, 9);
	//quick_sort_op(arr, 0, 9);
	//quicksort_nonrecursive(arr, 0, 9);
	//merge_sort(arr, 10);
	//merge_sort_r(arr, 10);
	show_arr(arr, 10);
	return 0;
}
