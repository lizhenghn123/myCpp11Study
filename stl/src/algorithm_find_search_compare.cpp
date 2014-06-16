// ***********************************************************************
// Filename         : algorithm_find_compare.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : 包含了STL中的非变易算法(查找、比较、最大最小值等)
//
// Last Modified By : LIZHENG
// Last Modified On : 2013-07-22
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//! STL的非变易算法（Non-mutating algorithms）是一组不破坏操作数据的模板函数，用来对序列数据进行逐个处理、元素查找、子序列搜索、统计和匹配。
//! find find_if find_if_not adjacent_find find_end find_first_of
//! search search_n binary_search lower_bound upper_bound equal_range
//! max min max_element min_element mismatch lexicographical_compare
//! includes equal count count_if all_of any_of none_of
template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

//find          : 查找等于某值的元素
//find_if       : 是find的一个谓词判断版本，它利用返回布尔值的谓词判断pred，检查迭代器区间[first, last)上的每一个元素
//find_if_not   : 返回第一个值不满足给定条件的元素
//adjacent_find : 用于查找相等或满足条件的邻近元素对。
//find_end      : 在一个序列中搜索出最后一个与另一序列匹配的子序列.
//                在迭代器区间[first1, last1)中搜索出与迭代器区间[first2, last2)元素匹配的子序列，返回首元素的迭代器或last1
//find_first_of : 用于查找位于某个范围之内的元素。在迭代器区间[first1, last1)上查找元素*i，使得迭代器区间[first2, last2)
//                有某个元素*j，满足*i ==*j或满足二元谓词函数comp(*i, *j)==true的条件。元素找到则返回迭代器i，否则返回last1
void test_find()
{
	{	//find find_if find_if_not
		std::cout << "--------------------    find find_if find_if_not --------------------\n";
		vector<int> vvv = { 16, 2, 30, 3, 45, 75, 69, 70 };
		print_all(vvv.begin(), vvv.end());

		int val = 3;
		auto iter = std::find(vvv.begin(), vvv.end(), val);
		if (iter != vvv.end())
			cout << "find it, " << "elem " << val << " at location " << iter - vvv.begin() << "\n";
		else
			cout << "find fail, no elem " << val << "\n";

		//查找第一个能够整除val的元素位置
		auto iter2 = std::find_if(vvv.begin(), vvv.end(), [&val](int x){ return x % val == 0; });
		if (iter2 != vvv.end())
			cout << "find it, at location " << iter2 - vvv.begin() << ", and value = " << *iter2 << "\n";
		else
			cout << "find fail\n";

		auto iter3 = std::find_if_not(vvv.begin(), vvv.end(), [&val](int x){ return x < 50; });
		if (iter2 != vvv.end())
			cout << "find it, at location " << iter2 - vvv.begin() << ", and value = "<< *iter3 << "\n";
		else
			cout << "find fail\n";
	}
	{	//adjacent_find
		std::cout << "--------------------    adjacent_find  --------------------\n";
		int IntArray[] = { 1, 2, 3, 4, 10, 8, 8, 6, 7, 9 };
		const int ARRAY_SIZE = sizeof(IntArray) / sizeof(IntArray[0]);
		print_all(IntArray, IntArray + ARRAY_SIZE);

		// 查找第一对相邻且相等的元素 
		int *pos1 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE);
		if (pos1 != IntArray + ARRAY_SIZE)  // elements found		
			cout << "Found adjacent pair of matching elements: (" << *pos1 << ", "
			<< *(pos1 + 1) << "), " << "at location " << pos1 - IntArray << endl;
		else
			cout << "No adjacent pair of matching elements were found" << endl;

		// 带谓词形式的查找满足条件odd_even的邻近元素对位置
		//x bool odd_even(int x, int y)
		//x {
		//x 	return (x - y) % 2 == 0 ? 1 : 0;
		//x }
		//x int *pos2 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE, odd_even);
		int *pos2 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE, [](int x, int y){ return (x - y) % 2 == 0 ? 1 : 0; });
		if (pos2 != IntArray + ARRAY_SIZE)  // elements found		
		{
			cout << "Found adjacent pair of matching elements: (" << *pos2 << ", "
				<< *(pos2 + 1) << "), " << "at location " << pos2 - IntArray << endl;
		}
		else
			cout << "No adjacent pair of matching elements were found" << endl;
	}
	{	//find_end
		std::cout << "--------------------    find_end   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
		//sort(v.begin(), v.end()); 
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		vector<int>::iterator iter;

		vector<int> arr = { 1, 2, 2 };
		iter = std::find_end(v.begin(), v.end(), arr.begin(), arr.end());
		if (iter != v.end())
			cout << "find at position " << (iter - v.begin()) << endl;
		else
			cout << "find fail\n";

		vector<int> arr1 = { 1, 2, 2, 9 };
		iter = std::find_end(v.begin(), v.end(), arr1.begin(), arr1.end());
		if (iter != v.end())
			cout << "find at position " << (iter - v.begin()) << endl;
		else
			cout << "find fail\n";

		vector<int> arr2 = { 3, 8, 4 };
		//查找一个原序列中某一连续子序列，使其值加1后恰巧为新序列arr2
		iter = std::find_end(v.begin(), v.end(), arr2.begin(), arr2.end(), [](int x, int y){ return x + 1 == y;	});
		if (iter != v.end())
			cout << "find at position " << std::distance(v.begin(), iter) << endl;
		else
			cout << "find fail\n";
	}
	{	//find_first_of
		std::cout << "--------------------    find_first_of   --------------------\n";
		const char* hello = "Hello, World!";
		const char* email = "lizhenghn@gmail.com";
		const char* pos = std::find_first_of(hello, hello + strlen(hello), email, email + strlen(email));
		if (pos!=NULL)
			cout << "字符串hello中第一个出现在字符串email的字符为：" << *pos << endl;
	}
}

//searc         : 给出两个范围，在一个序列中找另一个序列的第一次出现的位置。
//search_n      : 搜索序列中是否有一系列元素值均为某个给定值(或者满足谓词判断条件）的子序列。
//                这两个函数并不要求有序，它们只是按顺序开始查找搜索
//binary_search : 二分查找，要求待查序列必须有序. 查找是否在[first, last)中存在iterator i, 
//                满足 !(*i<value) && !(value<*i) or comp(*i, value) == false && comp(value, *i) == false
void test_search()
{
	std::cout << "--------------------    search   --------------------\n";

	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6, 4 };
	//x sort(v.begin(), v.end());   //注意，必须要保证排序过的
	print_all(v.begin(), v.end());

	{   //search
		auto func = [](std::vector<int> &vec){ copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ",")); return ""; };

		vector<int> v1 = { 2, 7, 3 };
		vector<int>::iterator iter1 = std::search(v.begin(), v.end(), v1.begin(), v1.end());
		if (iter1 != v.end())
			cout << "v have sub sequences is v1(", func(v1), cout << ")\n";
		else
			cout << "v have not sub sequences is v1(", func(v1), cout << ")\n";

		vector<int> v2 = { 2, 7, 3, 5 };
		vector<int>::iterator iter2 = std::search(v.begin(), v.end(), v2.begin(), v2.end());
		if (iter2 != v.end())
			cout << "v have sub sequences is v2\n";
		else
			cout << "v have not sub sequences is v2\n";
	}
	{   //search_n
		int count = 3, val = 4;
		if (std::search_n(v.begin(), v.end(), count, val) != v.end())
			cout << "find " << count << " continuous sequencs is " << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs is " << val << "\n";

		count = 2, val = 7;
		if (std::search_n(v.begin(), v.end(), count, val) != v.end())
			cout << "find " << count << " continuous sequencs is" << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs is" << val << "\n";

		count = 3, val = 8;
		if (std::search_n(v.begin(), v.end(), count, val, [](int elem, int val){ return elem * 2 == val; }) != v.end())
			cout << "find " << count << " continuous sequencs which its double is " << val << "\n";
		else
			cout << "find " << count << " continuous sequencs which its double is " << val << "\n";

		count = 4, val = 8;
		if (std::search_n(v.begin(), v.end(), count, val, [](int elem, int val){ return elem * 2 == val; }) != v.end())
			cout << "find " << count << " continuous sequencs which its plus one is " << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs which its plus one is " << val << "\n";
	}
	{	// binary_search
		std::cout << "--------------------    binary_search   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 5, 6, 6 };
		sort(v.begin(), v.end());   //注意，必须要保证排序过的		
		print_all(v.begin(), v.end());
		
		int val = 3;
		if (std::binary_search(v.begin(), v.end(), val))
			cout << "find elem " << val << " success\n";
		else
			cout << "find elem " << val << " fail\n";

		//val = 9;
		//查找 满足两者相减能够被2整除的元素
		if (std::binary_search(v.begin(), v.end(), val, [](int elem, int val)->bool{ return abs(val - elem) % 2 == 0; }))
			cout << "find success\n";
		else
			cout << "find fail\n";
		std::cout << "\n";
	}
}

//lower_bound : 返回指向范围中第一个值大于或等于给定值的元素的迭代器
//upper_bound : 返回指向范围中第一个值大于给定值的元素的迭代器
//假定相同值的元素可能有多个,lower_bound 返回第一个符合条件的元素位置;upper_bound 返回最后一个符合条件的元素位置
void test_lower_upper_bound()
{
	{	//lower_bound
		std::cout << "--------------------    lower_bound   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
		sort(v.begin(), v.end());   //注意，必须要保证排序过的
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		/*  lower_bound */
		int val = 3;
		cout << "lower_bound function, split value = " << val << endl;
		vector<int>::iterator iter = std::lower_bound(v.begin(), v.end(), val);
		cout << "less than " << val << " : ";
		copy(v.begin(), iter, ostream_iterator<int>(cout, " "));		cout << endl;
		cout << "equal or greater than " << val << " : ";
		copy(iter, v.end(), ostream_iterator<int>(cout, " "));			cout << endl;
		std::cout << "\n";
	}
	{	//upper_bound
		std::cout << "--------------------    upper_bound   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 5, 6, 6 };

		sort(v.begin(), v.end());   //注意，必须要保证排序过的

		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		int val = 3;
		cout << "upper_bound function, split value = " << val << endl;
		vector<int>::iterator iter = std::upper_bound(v.begin(), v.end(), val);
		cout << "equal or less than " << val << " : ";
		copy(v.begin(), iter, ostream_iterator<int>(cout, " "));		cout << endl;
		cout << "greater than " << val << " : ";
		copy(iter, v.end(), ostream_iterator<int>(cout, " "));			cout << endl;
		std::cout << "\n";
	}
}

//equal_range : 顺序查找等于给定值的元素组成的子范围，要求待查序列必须有序
//              查找最大的subrange[i,j)，使得任意一个iterator in [i,j)满足!(*k<value) && !(value<*k) or comp(*k,value)==false && comp(value,*k)==false.
//              假定相同值的元素可能有多个,equal_range 返回所有等于指定值的头/尾元素的位置，其实就是lower_bound和upper_bound
void test_equal_range()
{
	std::cout << "--------------------    equal_range   --------------------\n";

	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
	sort(v.begin(), v.end());   //注意，必须要保证排序过的
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

	int val = 3;
	cout << "euqual_range function, split value = " << val << endl;
	pair<vector<int>::iterator, vector<int>::iterator> vecpair = std::equal_range(v.begin(), v.end(), val);
	cout << "get euqal value " << val << "= ";
	copy(vecpair.first, vecpair.second, ostream_iterator<int>(cout, " "));	cout << endl;

	val = 9;
	cout << "euqual_range function, split value = " << val << endl;
	vecpair = std::equal_range(v.begin(), v.end(), val);
	cout << "get euqal value " << val << "= ";
	copy(vecpair.first, vecpair.second, ostream_iterator<int>(cout, " "));	cout << endl;
	std::cout << "\n";
}

//equal       : 如果两个序列在标志范围内元素都相等，返回true
//includes    : 判断第一个指定范围内的所有元素是否都被第二个范围包含，使用底层元素的<操作符，成功返回true
//max         : 返回两个元素中较大一个
//min         : 返回两个元素中较小一个
//max_element : 返回一个ForwardIterator，指出序列中最大的元素
//min_element : 返回一个ForwardIterator，指出序列中最小的元素
//minmax      : 返回两个元素中值最大及最小的元素
//minmax_element : 返回给定范围中值最大及最小的元素
//mismatch    : 比较两个序列，返回一对iterator，标志第一个不匹配元素位置。如果都匹配，返回每个容器的last
//lexicographical_compare : 按字典序比较两个序列
void test_relation()
{
	vector<int> v1 = { 1, 2, 3, 4, 4, 5, 6, 6, 6, 9 };  //集合操作时必须要求序列有序
	vector<int> v2 = { 8, 2, 3, 4, 5, 5, 6, 6 };  //集合操作时必须要求序列有序
	vector<int> v = { 2, 3, 5, 6, 9 };
	if (std::includes(v1.begin(), v1.end(), v.begin(), v.end()))
		cout << "v is subse of v1\n";
	if (std::lexicographical_compare(v1.begin(), v1.end(), v.begin(), v.end()))
		cout << "v is subse of v1\n";

	int arr[] = { 2, 3, 5, 6, 9 };
	if (std::equal(v.begin(), v.end(), arr))
		cout << "arr == v\n";

	auto it1 = std::max(v1, v2); //默认是逐元素比较，直至找到大小或结束
	print_all(it1.begin(), it1.end());
	auto it2 = std::min(v1, v2); //默认是逐元素比较，直至找到大小或结束
	print_all(it2.begin(), it2.end());

	auto it3 = std::max_element(v1.begin(), v1.end());
	cout << *it3 << "\n";
	auto it4 = std::min_element(v1.begin(), v1.end());
	cout << *it4 << "\n";

	auto it5 = std::minmax({ 3, 5, 8, 0, 1 });
	cout << it5.first << "\t" << it5.second << "\n";
	auto it6 = std::minmax_element(v1.begin() + 1, v1.end());
	cout << *it6.first << "\t" << *it6.second << "\n";

	vector<int> v3 = { 1, 2, 3, 4 };
	vector<int> v4 = { 1, 2, 3, 4, 5 };
	pair<vector<int>::iterator, vector<int>::iterator> pp1 = std::mismatch(v3.begin(), v3.end(), v4.begin());
	if (pp1.first == v3.end() && pp1.second != v4.end())
		cout << "v3 match v4";
	else
		cout << "different elem : " << *pp1.first << "\t" << *pp1.second << "\n";
}

//count       : 用于计算容器中的某个给定值的出现次数
//count_if    : 返回值满足给定条件的元素的个数
//all_of      : 检测在给定范围中是否所有元素都满足给定的条件
//any_of      : 检测在给定范围中是否存在元素满足给定的条件
//none_of     : 检测在给定范围中是否不存在元素满足给定的条件
void test_count()
{
	{	// count count_if
		vector<int> vvv = { 16, 70, 30, 3, 45, 75, 69, 70 };
		print_all(vvv.begin(), vvv.end());

		int val = 70;
		int cou = std::count(vvv.begin(), vvv.end(), 70);
		cout << "total have " << cou << " elems(" << val << ")\n";

		int cou2 = std::count_if(vvv.begin(), vvv.end(), [&val](int x){ return x >= 70; });
		cout << "total have " << cou2 << " elems which is equal or greater than(" << val << ")\n";
	}
	{	// all_of any_of none_of
		vector<int> vvv = { 16, 70, 30, 3, 45, 75, 69, 70 };
		if (std::all_of(vvv.begin(), vvv.end(), [](int e){ return e > 0; }))
			cout << "all of elems greater than 0\n";
		else 
			cout << "not all of elems greater than 0\n";

		if (std::any_of(vvv.begin(), vvv.end(), [](int e){ return e < 10; }))
			cout << "some of elems less than 10\n";
		else
			cout << "all of elems greater than 10\n";

		if (std::none_of(vvv.begin(), vvv.end(), [](int e){ return e > 90; }))
			cout << "none of elems greater than 90\n";
		else
			cout << "some of elems greater than 90\n";
	}
}

int main()
{
	test_find();
	std::cout << "===================\n";

	test_search();
	std::cout << "===================\n";

	test_lower_upper_bound();
	std::cout << "===================\n";

	test_equal_range();
	std::cout << "===================\n";

	test_relation();
	std::cout << "===================\n";

	test_count();
	std::cout << "===================\n";

	getchar();
	return 0;
}