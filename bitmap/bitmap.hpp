#pragma once

#include <iostream>
#include <vector>
using namespace std;

class bit_set{
	private:
		vector<size_t> datas;

		size_t converse(const size_t & val)
		{
			return val>>5; //相当于除32，取整
		}
	public:
		bit_set(size_t size)//构造函数，构造bitmap大小
		{
			//计算需要多少个int来存储这些数据
			//右移5 ＝ /32, ＋1，代表数据从0开始，最低比特为是0
			datas.reserve((size>>5) + 1);
			datas.assign((size>>5) + 1, 0);
		}
		~bit_set()
		{}
		//测试目标数据是否在bitmap中
		bool test(const size_t &value)
		{
			size_t index = converse(value);//将我们认知的数据转化成bitmap对应的位置(下标)
			size_t pos = value % 32;//目标数据的位置［偏移量］ 目标数据 ＝ datas［下标］＋ 偏移量
			return datas[index]&(1<<pos); //测试该位置是否置位
		}
		bool set(const size_t &value)
		{
			size_t index = converse(value);//将我们认知的数据转化成bitmap对应的位置(下标)
			size_t pos = value % 32;//目标数据的位置［偏移量］ 目标数据 ＝ datas［下标］＋ 偏移量
			datas[index] |= (1<<pos);//将目标bit位置设置
			return true;
		}
		bool reset(const size_t &value)
		{
			size_t index = converse(value);//将我们认知的数据转化成bitmap对应的位置(下标)
			size_t pos = value % 32;//目标数据的位置［偏移量］ 目标数据 ＝ datas［下标］＋ 偏移量
			datas[index] &= ~(1<<pos);//清空目标bit位置
			return true;
		}

		void clear()
		{
			datas.clear();
		}
};

