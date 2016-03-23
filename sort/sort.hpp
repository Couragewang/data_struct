#pragma once

#include <iostream>
#include <assert.h>
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
//思路：相邻数据比较将较大数据往后冒泡
int bubble_sort(int *arr, int size)
{
	assert(arr);

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

//插入排序, 固定元素找位置
int insert_sort(int *arr, int size)
{
	assert(arr);
	int i = 1;
	for( ; i < size; ++i ){
		int tmp = arr[i];//保存第i个元素
		int end = i - 1; //当前欲插入的数据的前一个位置
		//按照从小到大的顺序排序
		while(end >= 0  && tmp < arr[end]){
			arr[end+1] = arr[end];
			--end;
		}
		arr[end + 1] = tmp; //插入合适的位置,注意索引值
	}
	return 0;
}

//shell排序
//对插入排序的优化
//直接插入排序在序列完全逆序的时候，性能很差.（每次都全部要全部比较，同时有非常多次的移位操作）
//对于插入排序，如果待排序数据越接近有序，则数据移动次数越少,插入排序性能较高.
//思路： 待排序列有n个元素，先取一个小于n的整数h1作为第一个增量，把待排序列以间隔h1分成若干子序列，
//       子序列内使用插入排序；然后取第二个增量h2(< h1)，重复上述的划分和排序，直至所取的增量hl = 1 (h1 > h2 > ... > hl)。
//结论： 这样不管序列多么庞大，在先前较大步长分组下每个子序列规模都不是很大，用直接插入效率很高；
//后面步长变小，子序列变大，但由整体有序性越来越明显，排序效率依然很高，大大提高了时间效率。
int shell_sort(int *arr, int size)
{
	assert(arr);

	int step = size;
	while(step > 1){

		//了解步长的选择, Knuth提出的增量效果更好
		step = step/3 + 1; //选择步长，划分子序列

		//使用插入排序
		int curr = step;
		for( ; curr < size; ++curr ){
			int end = curr - step;
			int tmp = arr[curr];
			//小 -> 大，小数据前移
			while(end >= 0 && tmp < arr[end]){
				arr[end + step] = arr[end];//大数据后移
				end -= step; //更新索引，继续往前找
			}
			arr[end + step] = tmp;//将比较的tmp数据，放到该step序列的合理位置
		}
	}
	return 0;
}

//选择排序，固定位置找元素
//思路: 序列中先找到最小的，然后放到第一个位置。之后再看剩余元素中最小的，
//      放到第二个位置……以此类推，就可以完成整个的排序工作
int select_sort(int *arr, int size)
{
	assert(arr);

	for(int begin = 0; begin < size - 1; ++begin){//begin表示固定的位置
		int min_index = begin;
		for(int curr_index = begin + 1; curr_index < size; ++curr_index){
			if(arr[min_index] > arr[curr_index]){ //小->大
				min_index = curr_index; //更新最小数据下标
			}
		}
		if(min_index != begin){
			swap(arr[min_index], arr[begin]);//将最小数据交换到当前固定的位置处
		}
	}
	return 0;
}

//选择排序优化，固定首尾两个位置来进行交换, 一次找到最大和最小值
int select_sort_op(int *arr, int size)
{
	assert(arr);

	int begin = 0; //首下标
	int end = size -1;//尾下标

	while(begin < end){//固定首尾位置 
		//找到最大和最小数据，并放到首尾
		int curr = begin;
		while(curr < end){
			if(arr[curr] < arr[begin]){//找到较小数据
				swap(arr[curr], arr[begin]);//遍历一次，肯定找到最小的数据, 并且该数据在合适的位置上
			}
			if(arr[curr] > arr[end]){//同上
				swap(arr[curr], arr[end]); //同上
			}
			++curr;
		}
		//更新范围
		++begin;
		--end;
	}
	return 0;
}































