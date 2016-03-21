#pragma once
#include <iostream>
using namespace std;
void show_arr(int arr[], int size)
{
	for(int i = 0; i<size; i++){
		cout<<"\t"<<arr[i];
	}
	cout<<endl;
}

static void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

//冒泡排序
int bubble_sort(int *arr, int size)
{
	int end = 0; //定位到数组最后一个元素
	for( end = size - 1; end > 0; end-- ){
		int flag = 0;
		for( int i = 0; i < end; i++ ){
			if(arr[i] > arr[i+1]){
				swap(arr[i], arr[i+1]);
				flag = 1;
			}
		}
		if( flag == 0 ){
			break;
		}
	}
	return 0;
}
