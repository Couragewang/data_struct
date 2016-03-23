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
	select_sort(arr, 10);
	show_arr(arr, 10);
	return 0;
}
