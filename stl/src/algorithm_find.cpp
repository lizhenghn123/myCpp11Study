#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//! C++STL的非变易算法（Non-mutating algorithms）是一组不破坏操作数据的模板函数，用来对序列数据进行逐个处理、元素查找、子序列搜索、统计和匹配。

template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

///find算法用于查找等于某值的元素。如果迭代器iter所指的元素满足*iter == value ，则返回迭代器iter，未找则返回last。
///find_if算法 是find的一个谓词判断版本，它利用返回布尔值的谓词判断pred，检查迭代器区间[first, last)上的每一个元素，
///如果迭代器iter满足pred(*iter) == true，表示找到元素并返回迭代器值iter；未找到元素，则返回last。
void test_find()
{
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
		cout << "find it, at location " << iter2 - vvv.begin() << "\n";
	else
		cout << "find fail\n";
}

///adjacent_find算法用于查找相等或满足条件的邻近元素对。其有两种函数原型：
///一种在迭代器区间[first , last)上查找两个连续的元素相等时，返回元素对中第一个元素的迭代器位置;
///另一种是使用二元谓词判断binary_pred，查找迭代器区间[first , last)上满足binary_pred条件的邻近元素对，未找到则返回last。
void test_adjacent_find()
{
	int IntArray[] = { 1, 2, 3, 4, 10, 8, 8, 6, 7, 9 };
	const int ARRAY_SIZE = sizeof(IntArray) / sizeof(IntArray[0]);
	print_all(IntArray, IntArray + ARRAY_SIZE);

	// 查找第一对相邻且相等的元素 
	int *pos1 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE);
	if (pos1 != IntArray + ARRAY_SIZE)  // elements found		
		cout << "Found adjacent pair of matching elements: (" << *pos1 << ", " 
		     << *(pos1 + 1) << "), " <<	"at location " << pos1 - IntArray << endl;
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

///find_end: 在一个序列中搜索出最后一个与另一序列匹配的子序列.
///在迭代器区间[first1, last1)中搜索出与迭代器区间[first2, last2)元素匹配的子序列，返回首元素的迭代器或last1
///并不要求有序，它们只是按顺序开始查找搜索
void test_find_end()
{
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

///find_first_of算法用于查找位于某个范围之内的元素。在迭代器区间[first1, last1)上查找元素*i，使得迭代器区间[first2, last2)
///有某个元素*j，满足*i ==*j或满足二元谓词函数comp(*i, *j)==true的条件。元素找到则返回迭代器i，否则返回last1
void test_find_first_of()
{
	const char* strOne = "abcdef1212daxs";
	const char* strTwo = "2ef";
	const char* result = find_first_of(strOne, strOne + strlen(strOne),	strTwo, strTwo + strlen(strTwo));
	cout << "字符串strOne中第一个出现在strTwo的字符为：" << *result << endl;
}

///count算法用于计算容器中的某个给定值的出现次数。它有两个使用原型，均计算迭代器区间[first, last)上等于value值
///的元素个数n，区别在于计数n是直接返回还是引用返回。
void test_count()
{
	vector<int> vvv = { 16, 70, 30, 3, 45, 75, 69, 70 };
	print_all(vvv.begin(), vvv.end());

	int val = 70;
	int cou = std::count(vvv.begin(), vvv.end(), 70);
	cout << "total have " << cou << " elems(" << val << ")\n";

	int cou2 = std::count_if(vvv.begin(), vvv.end(), [&val](int x){ return x >= 70; });
	cout << "total have " << cou2 << " elems which is equal or greater than(" << val << ")\n";
}

///binary_search: 二分查找，要求待查序列必须有序
///查找是否在[first, last)中存在iterator i, 满足 !(*i<value) && !(value<*i) or comp(*i, value) == false && comp(value, *i) == false
void test_binary_search()
{
	std::cout << "--------------------    binary_search   --------------------\n";
	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 5, 6, 6 };
	sort(v.begin(), v.end());   //注意，必须要保证排序过的		
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// binary_search
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

///search: 给出两个范围，在一个序列中找另一个序列的第一次出现的位置。
///search_n: 搜索序列中是否有一系列元素值均为某个给定值(或者满足谓词判断条件）的子序列。
///这两个函数并不要求有序，它们只是按顺序开始查找搜索
void test_search()
{
	std::cout << "--------------------    search   --------------------\n";

	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6, 4 };
	//x sort(v.begin(), v.end());   //注意，必须要保证排序过的
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

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
}

///lower_bound: 查找最远的一个iterator i， 使得[first,i)里面的任意一个iterator j，有 *j < value or comp(*j,value)==true. 
///返回一个Iterator，指向在有序序列范围内的可以插入指定值而不破坏容器顺序的第一个位置.重载函数使用自定义比较操作
///upper_bound: 查找最远的一个iterator i， 使得[first,i)里面的任意一个iterator j，有 !(*j < value) or comp(*j,value)==false. 
///返回一个ForwardIterator,指向在有序序列范围内插入value而不破坏容器顺序的最后一个位置，该位置标志一个大于value的值。
///假定相同值的元素可能有多个,lower_bound 返回第一个符合条件的元素位置;upper_bound 返回最后一个符合条件的元素位置
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

///equal_range: 顺序查找，要求待查序列必须有序
///查找最大的subrange[i,j)，使得任意一个iterator in [i,j)满足!(*k<value) && !(value<*k) or comp(*k,value)==false && comp(value,*k)==false.
///假定相同值的元素可能有多个,equal_range 返回所有等于指定值的头/尾元素的位置，其实就是lower_bound和upper_bound
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

int main()
{
	test_find();
	std::cout << "===================\n";

	test_adjacent_find();
	std::cout << "===================\n";

	test_find_end();
	std::cout << "===================\n";

	test_find_first_of();
	std::cout << "===================\n";

	test_count();
	std::cout << "===================\n";

	test_binary_search();
	std::cout << "===================\n";

	test_search();
	std::cout << "===================\n";

	test_lower_upper_bound();
	std::cout << "===================\n";

	test_equal_range();
	std::cout << "===================\n";

	getchar();
	return 0;
}