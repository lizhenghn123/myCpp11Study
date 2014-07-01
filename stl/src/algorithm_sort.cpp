// ***********************************************************************
// Filename         : algorithm_sort.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : STL中的排序算法及其他通用算法
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
#include <numeric>
#include <functional>
#include <cstdlib>
using namespace std;

//! sort stable_sort partial_sort partial_sort_copy partition stable_partition nth_element merge inplace_merge
//     排序和通用算法 14个
//merge             : 合并两个有序序列，存放到另一个序列。重载版本使用自定义的比较
//inplace_merge     : 合并两个有序序列，结果序列覆盖两端范围。重载版本使用输入的操作进行排序
//nth_element       : 将范围内的序列重新排序，使所有小于第n个元素的元素都出现在它前面，而大于它的都出现在后面
//partial_sort      : 对序列做部分排序，被排序元素个数正好可以被放到范围内
//partial_sort_copy : 与partial_sort类似，不过将经过排序的序列复制到另一个容器
//partition         : 对指定范围内元素重新排序，使用输入的函数，把结果为true的元素放在结果为false的元素之前
//stable_partition  : 与partition类似，不过保证保留容器中的相对顺序
//random_shuffle    : 对指定范围内的元素随机调整次序。重载版本输入一个随机数产生操作
//shuffle           : 用指定的随机数引擎随机打乱指定范围中的元素的位置
//reverse           : 将指定范围内元素重新反序排序
//reverse_copy      : 与reverse类似，不过将结果写入另一个容器
//rotate            : 将指定范围内元素移到容器末尾，由middle指向的元素成为容器第一个元素
//rotate_copy       : 与rotate类似，不过将结果写入另一个容器
//sort              : 以升序重新排列指定范围内的元素。重载版本使用自定义的比较操作
//stable_sort       : 与sort类似，不过保留相等元素之间的顺序关系(即：稳定排序) 
//is_sorted         : C11版本，判断序列是否为排序过的
//is_sorted_until   : 返回序列从start iterator开始为升序的子序列的结束处
template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

void test_sort()
{
	{	// sort  stable_sort
		std::cout << "--------------   sort stable_sort   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, rand); //产生10个随机数

		std::sort(v1.begin(), v1.end()); //默认升序
		print_all(v1.begin(), v1.end());

		vector<int> v2;
		std::generate_n(std::back_inserter(v2), 10, rand); //产生10个随机数

		std::sort(v2.begin(), v2.end(), std::greater<int>()); //降序
		//std::sort(v1.rbegin(), v1.rend());   // OK
		print_all(v2.begin(), v2.end());

		vector<int> v3 = { 3, 2, 1, 1, 2, 5, 7 };
		std::stable_sort(v3.begin(), v3.end()); //稳定排序，相同值仍保持原次序
		print_all(v3.begin(), v3.end());
	}
	{	// is_sorted  is_sorted_until 
		vector<int> v1 = { 3, 1, 20, 4, 5, 9, 8 };
		if (std::is_sorted(v1.begin(), v1.end()))  //v1 is not sorted
			cout << "v1 is sorted\n";
		else
			cout << "v1 is not sorted\n";

		if (std::is_sorted(v1.begin() + 1, v1.end() - 1))  //subset of v1 is sorted
			cout << "subset of v1 is sorted\n";
		else
			cout << "subset of v1 is not sorted\n";

		vector<int>::iterator it_end = std::is_sorted_until(v1.begin(), v1.end());
		print_all(v1.begin(), it_end);   // 3 

		vector<int>::iterator it_start = v1.begin() + 1;
		it_end = std::is_sorted_until(it_start, v1.end());
		print_all(it_start, it_end);    // 1 20

		it_start = v1.begin() + 2;
		it_end = std::is_sorted_until(it_start, v1.end(), std::greater<int>());
		print_all(it_start, it_end);    // 1 20
	}
	{	// partial_sort
		std::cout << "--------------   partial_sort   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //产生10个随机数
		print_all(v1.begin(), v1.end());

		std::partial_sort(v1.begin(), v1.begin() + 3, v1.end()); //只关心最小的三个数，不考虑其他（也即无序）
		print_all(v1.begin(), v1.end());

		std::partial_sort(v1.begin(), v1.begin() + 3, v1.end(), std::greater<int>()); //只关心最大的三个数，不考虑其他
		print_all(v1.begin(), v1.end());

		std::partial_sort(v1.begin(), v1.begin() + v1.size(), v1.end()); //相当于直接排序了
		print_all(v1.begin(), v1.end());
	}
	{	// partial_sort_copy
		std::cout << "--------------   partial_sort_copy   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //产生10个随机数
		print_all(v1.begin(), v1.end());

		vector<int> v2(v1.size());
		std::partial_sort_copy(v1.begin(), v1.end(), v2.begin(), v2.end());
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		vector<int> v3(v1.size());
		std::partial_sort_copy(v1.begin() + 3, v1.end(), v3.begin(), v3.end());
		print_all(v1.begin(), v1.end());
		print_all(v3.begin(), v3.end());
	}
	{	// partition
		std::cout << "--------------   partition   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //产生10个随机数
		print_all(v1.begin(), v1.end());

		vector<int> v2(v1.size());
		std::partition(v1.begin(), v1.end(), [](int e){ return e > 50; }); //将大于50的数放在前面，不考虑排序
		print_all(v1.begin(), v1.end());

		int oddeven[] = { 1, 2, 3, 4, 5, 6 };
		std::partition(oddeven, oddeven + 6, [](int x){ return x % 2 != 0; }); //排序，将奇数放在偶数之前
		print_all(oddeven, oddeven + 6);
	}
	{	// stable_partition
		std::cout << "--------------   stable_partition   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //产生10个随机数
		print_all(v1.begin(), v1.end());

		vector<int> v2(v1.size());
		std::stable_partition(v1.begin(), v1.end(), [](int e){ return e > 50; }); //将大于50的数放在前面，次序保持不变
		print_all(v1.begin(), v1.end());

		int oddeven[] = { 1, 2, 3, 4, 5, 6 };
		std::stable_partition(oddeven, oddeven + 6, [](int x){ return x % 2 != 0; }); //排序，将奇数放在偶数之前
		print_all(oddeven, oddeven + 6);
	}
	{	// merge inplace_merge
		vector<int> v1 = { 1, 3, 4, 9 };
		int arr[] = { 2, 6, 7 };

		vector<int> v2(v1.size() + sizeof(arr) / sizeof(0[arr]));

		std::merge(v1.begin(), v1.end(), arr, arr + sizeof(arr) / sizeof(0[arr]), v2.begin()); //必须有序
		print_all(v2.begin(), v2.end());

		vector<int> v3 = { 1, 3, 6, 9, 2, 5, 8 };  //[0, 4)和[4, 7)分别升序，将这两段序列合并，升序排列的范围[0, 7)
		auto it = adjacent_find(v3.begin(), v3.end(), std::greater<int>());
		std::inplace_merge(v3.begin(), v3.begin() + 4, v3.end());
		print_all(v3.begin(), v3.end());
	}
	{	// nth_element random_shuffle shuffle
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //产生10个随机数
		print_all(v1.begin(), v1.end());

		std::nth_element(v1.begin(), v1.begin() + 1, v1.end()); //将最小的元素放在序列前面
		print_all(v1.begin(), v1.end());

		std::sort(v1.begin(), v1.end());
		std::random_shuffle(v1.begin(), v1.end());
		print_all(v1.begin(), v1.end());

		std::sort(v1.begin(), v1.end());
		//std::shuffle(v1.begin(), v1.end(), rand);
		print_all(v1.begin(), v1.end());
	}
	std::cout << "======================\n";
}

int main()
{
	test_sort();
}