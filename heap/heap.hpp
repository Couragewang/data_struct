#pragma once

#include <iostream>
#include <assert.h>

//定义：二叉堆是完全二叉树或者是近似完全二叉树.
//满足特性：1. 父结点的键值总是大于或等于（小于或等于）任何一个子节点的键值。
//          2. 每个结点的左子树和右子树都是一个二叉堆（都是最大堆或最小堆）。
//最大堆：父结点的键值总是大于或等于任何一个子节点的键值时为最大堆。
//最小堆：父结点的键值总是小于或等于任何一个子节点的键值时为最小堆,此处按照最小堆讲解.
//一般将二叉堆简称堆
//堆的存储：一般都用数组来表示堆，i结点的父结点下标就为(i – 1) / 2。它的左右子结点下标分别为2 * i + 1和2 * i + 2。如第0个结点左右子结点下标分别为1和2。

static void show(int arr[], int size)
{
	int i = 0;
	for( ; i < size; ++i ){
		std::cout<<arr[i]<<" ";
	}
	std::cout<<std::endl;
}

static void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

//最小堆调整: 只有一个元素不符合堆定义，对它进行调整
//数据下调
static void min_heap_fix_down(int *arr/*堆数组*/, int start/*起始调整位置*/, int num/*数组元素总数*/)
{
	assert(arr);
	int tmp = arr[start];      //保存待调整数据
	int child = 2 * start + 1; //找到目标节点的左孩子
	while( child < num ){
		if( child+1 < num && arr[child] > arr[child+1] ){ //找到孩子节点中最小的节点
			++child;
		}
		if( arr[child] >= tmp ){ //最小节点就是当前start节点，不需要调整
			break;
		}
		//开始调整
		arr[start] = arr[child]; //元素内容上移
		start      = child;      //起始坐标更新
		child      = 2*start+1;  //孩子节点更新,至此就是原始问题的子问题，处理方式一样，规模变小
	}
	arr[start] = tmp; //放入合适的位置
}

//堆操作之堆化数组
//注意：先了解堆的插入和删除，再来学习如何对一个数组进行堆化操作。
//思路: 对一颗完全或近似完全的二叉树而言，所有的叶子节点都自成一个合法的堆。
//      所以，调整从最后一个叶子节点的父节点开始,逐次往上调整(更新父节点). 而单次调整过程，可以看作将新节点(父节点)插入堆的过程!
void make_min_heap(int arr[], int size)
{
	int last_father = size/2 - 1;
	for(; last_father >= 0; --last_father){
		min_heap_fix_down(arr/*堆数组*/, last_father/*起始调整位置*/, size/*数组元素总数*/);
	}
}

//堆操作之堆的删除
//思路： 按定义，堆中每次都只能删除第0个数据。为了便于重建堆，
//       实际的操作是将最后一个数据的值赋给根结点，然后再从根
//       结点开始进行一次从上向下的调整。调整时先在左右儿子结
//       点中找最小的，如果父结点比这个最小的子结点还小说明不
//       需要调整了，反之将父结点和它交换后再考虑后面的结点。
//       相当于从根结点将一个数据的“下沉”过程。
void min_heap_delete(int arr[], int size, int &out)
{
	out = arr[0];
	swap(arr[0], arr[size-1]);
	min_heap_fix_down(arr/*堆数组*/, 0/*起始调整位置*/, size-1/*数组元素总数*/);
	return;
}

//新数据上调
//思路:每次插入都是将新数据放在数组最后, 为叶子节点。可以发现从这个新数据的父结点到根结点必然为一个有序的数列(最小堆＋每个节点都只有一个父节点)
//     当我对新节点进行调整的时候，原则遵照堆的定义并且目前只有该数据暂时不满足堆定义,所以调整堆对堆本身的整体结构并不影响!
//	   现在的任务是将这个新数据插入到这个有序数据中——这就类似于直接插入排序中将一个数据并入到有序区间中
static void min_heap_fix_up(int arr[], int size)
{
	int i = size - 1;
	int tmp = arr[i];//新插入数据
	int j = (i-1)/2;
	while(j >= 0 && i > j){ //确认一下, 再想想
		if(arr[j] <= tmp){
			break;//小数据上移
		}
		arr[i] = arr[j]; //父节点下沉
		i = j;
		j = (j-1)/2; 
	}
	arr[i] = tmp;
}

//堆操作之堆的插入
void min_heap_add(int arr[], int size, int in)
{
	arr[size] = in;
	min_heap_fix_up(arr, size+1);
}

//堆操作之堆排
//首先可以看到堆建好之后堆中第0个数据是堆中最小的数据。取出这个数据再执行下堆的删除操作。
//这样堆中第0个数据又是堆中最小的数据，重复上述步骤直至堆中只有一个数据时就直接取出这个数据。
//由于堆也是用数组模拟的，故堆化数组后，第一次将A[0]与A[n - 1]交换，再对A[0…n-2]重新恢复堆。
//第二次将A[0]与A[n – 2]交换，再对A[0…n - 3]重新恢复堆，重复这样的操作直到A[0]与A[1]交换。
//由于每次都是将最小的数据并入到后面的有序区间，故操作完成后整个数组就有序了。有点类似于直接选择排序。
void head_sort(int arr[], int size)
{
	for(int i = size-1; i>=1; --i){
		swap(arr[i], arr[0]);
		min_heap_fix_down(arr/*堆数组*/, 0/*起始调整位置*/, i/*数组元素总数*/);
	}
}

//后记：有时间在写吧...
