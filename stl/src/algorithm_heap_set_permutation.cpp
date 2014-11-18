// ***********************************************************************
// Filename         : algorithm_heap_set_permutation.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : 包含了STL中的堆算法、集合算法、排列算法等
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-14
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <assert.h>
using namespace std;

//! set_union set_intersection set_difference set_symmetric_difference
//! make_heap push_heap pop_heap sort_heap
//! next_permutation prev_permutation

template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

//集合操作算法
//includes                 : 判断一个集合是否是另一个集合的子集
//set_union                : 构造一个有序序列，包含两个序列中所有的不重复元素.
//set_intersection         : 构造一个有序序列，其中元素在两个序列中都存在.
//set_difference           : 构造一个有序序列，该序列仅保留第一个序列中存在的而第二个中不存在的元素.
//set_symmetric_difference : 构造一个有序序列，该序列取两个序列的对称差集(并集-交集)
//! 这些算法都需要查找两个集合，这两个集合都需要是有序且有相同的排序规则
void test_set_algorithm()
{
	vector<int> v1 = { 1, 2, 3, 4, 4, 5, 6, 6, 6, 9 };  //集合操作时必须要求序列有序
	vector<int> v2 = { 0, 2, 3, 4, 5, 5, 6, 6 };  //集合操作时必须要求序列有序
	vector<int> v = { 2, 3, 5, 6, 9 };
	if (std::includes(v1.begin(), v1.end(), v.begin(), v.end()))
		cout << "v is subse of v1\n";
	cout << "order 1 : ";
	print_all(v1.begin(), v1.end());
	cout << "order 2 : ";
	print_all(std::begin(v2), std::end(v2));

	v.clear();
	std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));  //求并
	cout << "union : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v), [](int e1, int e2){ return (e1 < e2); }); //求并,默认即是
	cout << "union : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v)); //求交
	cout << "intersection : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::inserter(v, v.end())); //求差
	cout << "difference : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v)); //求对称差
	cout << "symmetric_difference : ";
	print_all(std::begin(v), std::end(v));
}

//堆操作算法
//make_heap : 把指定范围内的元素生成一个堆。默认是建立最大堆。对int类型，可以在第三个参数传入greater<int>()得到最小堆。
//pop_heap  : 并不真正把最大元素从堆中弹出，而是重新排序堆。它把first和last-1交换，
//            然后重新生成一个堆。可使用容器的back来访问被"弹出"的元素或者使用pop_back进行真正的删除
//push_heap : 假设first到last-1是一个有效堆，要被加入到堆的元素存放在位置last-1，重新生成堆。
//            在指向该函数前，必须先把元素插入容器后
//sort_heap : 对指定范围内的序列重新排序，它假设该序列是个有序堆。重载版本使用自定义比较操作
void test_heap_algorithm()
{
	vector<int> vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(rand() % 100);
	print_all(vec.begin(), vec.end());

	std::make_heap(vec.begin(), vec.end()); //建立大顶堆
	print_all(vec.begin(), vec.end());

	//加入数据: 先在容器中加入，再调用push_heap 
	vec.push_back(100);
	std::push_heap(vec.begin(), vec.end());
	print_all(vec.begin(), vec.end());

	//删除数据: 先调用pop_heap，再在容器中删除  
	std::pop_heap(vec.begin(), vec.end());
	vec.pop_back();
	print_all(vec.begin(), vec.end());

	//堆排序  
	std::sort_heap(vec.begin(), vec.end());
	print_all(vec.begin(), vec.end());
}

//排列组合算法
//next_permutation : 返回给定范围中的元素组成的下一个按字典序的排列
//prev_permutation : 返回给定范围中的元素组成的上一个按字典序的排列,如果不存在上一个序列则返回false
//is_permutation   : 判断一个序列是否是另一个序列的一种排序
void test_permutation_algorithm()
{
	{
		vector<int> v = { 1, 2, 3, 4 }; //全排列时需要保证升序，next_permutation向后取一个次大的
		int sum = 1;
		//print_all(v.begin(), v.end());
		bool over = std::next_permutation(v.begin(), v.end());
		while (over)
		{
			sum++;
			//print_all(v.begin(), v.end());
			over = std::next_permutation(v.begin(), v.end());
		}
		cout << "total have " << sum << " permutation\n";
	}
	{
		vector<int> v = { 4, 3, 2, 1 }; //全排列时需要保证降序，prev_permutation向前取一个次小的
		int sum = 1;
		bool over = std::prev_permutation(v.begin(), v.end());
		while (over)
		{
			sum++;
			//print_all(v.begin(), v.end());
			over = std::prev_permutation(v.begin(), v.end());
		}
		cout << "total have " << sum << " permutation\n";
	}
	{
		vector<int> v1 = { 1, 2, 3, 4 };
		vector<int> v2 = { 4, 3, 2, 1 };
		if (std::is_permutation(v1.begin(), v1.end(), v2.begin()))
			cout << "OK\n";
	}
	{   //求组合，7个元素中选3个
		int values[] = { 1, 2, 3, 4, 5, 6, 7 };
		int elements[] = { 1, 1, 1, 0, 0, 0, 0 };
		const size_t N = sizeof(elements) / sizeof(elements[0]);
		assert(N == sizeof(values) / sizeof(values[0]));
		std::vector<int> selectors(elements, elements + N);

		int count = 0;
		do
		{
			std::cout << ++count << ": ";
			for (size_t i = 0; i < selectors.size(); ++i)
			{
				if (selectors[i])
				{
					std::cout << values[i] << ", ";
				}
			}
			std::cout << std::endl;
		} while (prev_permutation(selectors.begin(), selectors.end()));
	}
}


int main()
{
	test_set_algorithm();
	std::cout << "===================\n";

	test_heap_algorithm();
	std::cout << "===================\n";

	test_permutation_algorithm();
	std::cout << "===================\n";

	getchar();
	return 0;
}