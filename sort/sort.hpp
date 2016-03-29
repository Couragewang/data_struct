#pragma once

#include <iostream>
#include <stack>
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

//堆排序
int heap_sort()
{
	//详情见heap章节，这里不在讲解
	return 0;
}

//快速排序
//思想：快速排序采用的思想是分治思想。
//      快速排序是找出一个元素（理论上可以随便找一个）作为基准(pivot),然后对数组进行分区操作,使基准左边元素的值都不大于基准值,基准右边的元素值 都不小于基准值，
//      如此作为基准的元素调整到排序后的正确位置。递归快速排序，将其他n-1个元素也调整到排序后的正确位置。最后每个元素都是在排序后的正确位置，排序完成。所以快
//      速排序算法的核心算法是分区操作，即如何调整基准的位置以及调整返回基准的最终位置以便分治递归.
//left和right都是下标

int get_mid_index(int arr[], int left, int right)
{
	int mid = left + ((right-left)>>1);
	//找出left right mid中的中间值，作为key
	if( arr[left] < arr[right] ){
		if( arr[mid] > arr[right] ){
			return right;            //mid > right > left
		}else if( arr[mid] < arr[left] ){
			return left;             //right > left > mid
		}else{
			return mid;              //right > mid > left
		}
	}else{
		if( arr[mid] > arr[left] ){
			return left;             //mid > left > right
		}else if( arr[mid] < arr[right] ){
			return right;            //left > right > mid
		}else{
			return mid;              //left > mid > right
		}
	}
}

//快排单次，挖坑法
int partion3(int arr[], int left, int right)
{
	int key_index = get_mid_index(arr, left, right);
	if(key_index != right){
		swap(arr[key_index], arr[right]);
	}
	int key = arr[right]; //right新坑
	int begin = left;
	int end   = right;

	while(begin < end){
		while(begin < end && arr[begin] <= key){ //从左->右查找大于key的值, 此时end是坑
			++begin;
		}
		//此时，在begin处找到一个大于key的数据，填旧坑，挖新坑
		if(begin < end){
			arr[end] = arr[begin];//此时begin成为了新坑,注意key值始终没有变化 
		}
		while(end > begin && arr[end] >= key){//从右->左查找小于key的值
			--end;
		}
		if(end > begin){
			arr[begin] = arr[end]; //此时end又重新成为了新坑
		}
	}
	arr[end] = key;
	return begin;
}

//快排单次，（Hoare霍尔版本)
int partion2(int arr[], int left, int right)
{
	//首先获得key
	int key_index = get_mid_index(arr, left, right);
	if(key_index != right){
		swap(arr[key_index], arr[right]);
	}
	int key = arr[right]; //right新坑
	int begin = left;
	int end   = right;

	while(begin < end){
		//从右往左寻找，找到第一个小于key的值，暂停
		while(begin < end && arr[end] >= key){
			--end;
		}
		//从左往右寻找，找到第一个大于key的值，暂停
		while(begin < end && arr[begin] <= key){
			++begin;
		}
		//此时，begin指向的数据大于key， end指向的数据小于key,交换位置
		if(begin < end){
			swap(arr[begin], arr[end]);
		}
	}
	if(begin != right){
		swap(arr[begin], arr[right]); //right 就是key值，在上面的操作中，肯定没有被移动，而begin指向最后和end重叠的数据，
	}
	return begin;
}

//快排单次, 前后指针版本
//
int partion1(int arr[], int left, int right)
{
	int key_index = get_mid_index(arr, left, right);
	if(key_index != right){
		swap(arr[key_index], arr[right]);
	}
	int key = arr[right];//right key值
	int curr = left;
	int prev = left-1;
	while(curr < right){
		if( arr[curr] < key && ++prev != curr ){
			swap(arr[prev], arr[curr]);
		}
		++curr;
	}
	swap(arr[++prev], arr[right]);
	return prev;
}

int quick_sort(int arr[], int left, int right)
{
	if(left < right){
		//int boundary = partion3(arr, left, right);
		int boundary = partion1(arr, left, right);
        quick_sort(arr, left, boundary-1);
        quick_sort(arr, boundary+1, right);
	}
	return 0;
}

//非递归实现快排
void quicksort_nonrecursive(int arr[], int left, int right)
{
	std::stack<int> _s;
	_s.push(right); //先右边界, 在左边界
	_s.push(left);

	int count = 0;
	while( !_s.empty() ){
		int start = _s.top();//取出左边界
		_s.pop();
		int end  = _s.top();//取出右边界
		_s.pop();
		std::cout<<"count : "<<count<<" start : "<<start<<" end : "<<end<<std::endl;
		count++;
		if(start < end){
			//这个过程，其实将以前一个较大的范围，划分成为了两个较小的范围，然后针对每个较小的范围，(较大范围消失，较小范围生成)分而治之
			int mid = partion3(arr, start, end);
			_s.push(mid-1);
			_s.push(start);
			_s.push(right);
			_s.push(mid+1);
		}else{
			std::cout<<"break! "<<start<<" : "<<end<<std::endl;
		}
	}
}

//快速排序优化：在数据序列较短的时候，用插入排序进行优化
void quick_sort_op(int arr[], int left, int right)
{
	if(left < right){
		int step = right - left;
		if(step < 13){
			insert_sort(arr+left, step + 1);
		}else{
	    	int boundary = partion1(arr, left, right);
            quick_sort_op(arr, left, boundary-1);
            quick_sort_op(arr, boundary+1, right);
		}
	}
}

//src: 源数据
//dst: 为归并所申请的临时中转空间
//begin, mid, end: 此次归并的区域，归并［beign， mid) 和 ［mid，end)，两个区域(注意，这两个区域，不一定等长), 并且，begin， mid， end都肯定在src的有效范围之内
void _merge(int src[], int dst[], int begin, int mid, int end)
{
	int begin1 = begin;
	int end1 = mid;

	int begin2 = mid;
	int end2 = end;

	int index = 0;//dst中元素的索引
	while( begin1 < end1 && begin2 < end2 ){
		//排序小－>大
		if(src[begin1] < src[begin2]){
			dst[index++] = src[begin1++];
		}else{
			dst[index++] = src[begin2++];
		}
	}
	//归并过程是开始只有两个元素进行归并的（1个数组可以认为有序）
	//归并后，2个元素依旧有序。所以，后续的多路归并，都是建立在
	//之前的已序基础之上的,所以后续的处理相对非常简单
	if(begin1 < end1){
		memcpy(&dst[index], &src[begin1], (end1-begin1)*sizeof(int));
	}
	if(begin2 < end2 ){
		memcpy(&dst[index], &src[begin2], (end2 - begin2)*sizeof(int));
	}
	//待归并的两个区域[begin, mid) 和 [mid, end)必定是在src的某个起始位置连续的
	memcpy(&src[begin], dst, (end - begin)*sizeof(int));
}

//归并排序
void merge_sort(int arr[], int size)
{
	int *src = arr;
	int *dst = new int[size]; //二路归并需要申请独立空间

	int gap = 1;//二路归并， 跨度为1
	int begin, mid, end;
	//归并的跨度最大是size/2, 最后一次二路归并
	while( gap < size ){
		int div  = 0;
		for(; div < size; div += 2*gap){
			begin = div; //每次begin位置必定合理有效
			mid = div + gap; //二路归并，[begin, mid), 半闭半开区间
			end = div + 2*gap; //［mid, end), 同上

			if( mid > size ){//有可能越界，需检测 
				mid = size;
			}
			if( end > size ){ //同上
				end = size;
			}
			_merge(src, dst, begin, mid, end);//开始二路归并
		}
		gap = 2*gap;
	}

	delete []dst;
}

//归并排序递归
//对一个区域进行归并递归排序
void merge_r(int *src, int *dst, int left, int right)
{
	if( left < right-1 ){ //需要保证是一个有效的区域，left 不能等于 right, 否则，在最后的_merge中，会memcpy拷贝出问题
		int mid = left + (right - left)/2;
		merge_r(src, dst, left, mid);
		merge_r(src, dst, mid, right);
		_merge(src, dst, left, mid, right);//开始二路归并
	}
}

//归并排序优化
//当递归到一定程度之后，小区域使用插入排序进行排序
void merge_r_op(int *src, int *dst, int left, int right)
{
	if(left < right){
		if( right - left < 5 ){
			insert_sort(src+left, right - left); //当区域长度小于5的时候，使用插入排序进行优化, 减少递归次数
			return;
		}
		int mid = left + (right - left)/2;
		merge_r_op( src, dst, left, mid );
		merge_r_op( src, dst, mid, right);
		_merge(src, dst, left, mid, right);//开始二路归并
	}
}

//递归完成归并
void merge_sort_r(int arr[], int size)
{
	int *src = arr;
	int *dst = new int[size];
	//merge_r_op(src, dst, 0, size);
	merge_r(src, dst, 0, size);
	delete []dst;
}
///////////////////////////////////////////////////////////
//非比较排序 －> 计数排序 & 基数排序

//计数排序
//计数排序要求待排序的元素的关键值是位于0-k之间的正整数。因而是个非常特殊的情况。
//输入数组A：元素关键值是 0-K的正整数，可以有重复值
//输出数组B：输出数组A的一个非减序列
//中间数组C：大小K，它的i(0<=i<=k)索引位置存储的是A元素集合和。
//这里意思是：原始数组A元素变成了中间数组C下标。
void sort_count(int *arr, int size)
{
	assert(arr);

	int max = arr[0];
	int min = arr[0];

	int i = 1;
	for( ; i < size; i++ ){
		if(max < arr[i]){
			max = arr[i]; //找到序列中最大数据
		}
		if(min > arr[i]){
			min = arr[i]; //找到序列中最小数据
		}
	}
	//cout<<max<<" "<<min<<endl;
	int range = max - min + 1;
	int *count = new int[range];
	memset(count, 0, sizeof(int)*range);
	// 统计min-max范围内数据的出现个数
	for( i = 0; i < size; i++ ){
		count[ arr[i] - min ]++; //统计数据出现的次数。下标的对应关系是，0代表最小元素
	}
	// 根据统计数据的个数进行排序
	int index = 0;
	for(i = 0; i < range; i++){
		while(count[i]--){
			arr[index++] = min + i;
		}
	}
	delete []count;
}

int get_max_bits(int *arr, int size)
{
	int max_bit = 1; //起初认为序列中都是个位数字
	int max = 10;//如果有大于十的数字，说明max_bit最少是2
	for(int i = 0; i < size; ++i){
		while( arr[i] >= max){ //统计当前元素的位数
			max *= 10;
			max_bit++;
		}
	}
	return max_bit;
}

//基数排序－桶排序
//最低位优先(Least Significant Digit first)法，简称LSD法
void radix_sort_LSD(int arr[], int size)
{
	//1. 需要获取到数组序列中元素最大数据位数（个十百千...）
	int max_bits = get_max_bits(arr, size);
	int *bucket = new int[size]; //桶
	int *count = new int[10];    //计数器

	memset(bucket, 0, sizeof(int)*size);

	int radix = 1;
	for(int bit = 1; bit <= max_bits; ++bit){
		memset(count, 0, sizeof(int)*10);

		//统计指定数据位置（个十百千...）的数据个数
		for(int i = 0; i < size; ++i){
			int k = (arr[i]/radix)%10;//计算当前个(十百千，与radix相关)位数据（0-9）
			count[k]++; //个(十百千，与radix相关)位为k的数据进行累加统计
		}//统计完成

		//统计出来针对不同的数据位置，数据在桶中的位置范围
		for(int i = 1; i < size; i++){
			count[i] = count[i-1]+count[i];
		}

		//将数据放到对应的桶中
		for(){
		}
	}
}










