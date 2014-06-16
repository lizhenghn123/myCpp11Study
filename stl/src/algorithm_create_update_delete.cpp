// ***********************************************************************
// Filename         : algorithm_create_update_delete.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : STL中的变易算法(生成、变异、修改、替换、删除等)
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
using namespace std;

//! 变易算法(Mutating algorithms)就是一组能够修改容器元素数据的模板函数，可进行序列数据的复制，变换等
//! fill fill_n for_each generate generate_n transform
//! copy copy_backward copy_if copy_n
//! swap iter_swap swap_ranges
//! replace replace_if replace_copy replace_copy_if
//! remove  remove_if  remove_copy  remove_copy_if
//! reverse reverse_copy rotate rotate_copy
//! unique unique_copy
template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

//! 生成和变异算法
//fill       : 将一个范围的元素赋值为给定值
//fill_n     : 将某个位置开始的 n 个元素赋值为给定值
//generate   : 将一个函数的执行结果保存到指定范围的元素中，用于批量赋值范围中的元素
//generate_n : 将一个函数的执行结果保存到指定位置开始的 n 个元素中
//transform  : 对指定范围中的每个元素调用某个函数以改变元素的值.
//             重载版本将操作作用在一对元素上，另外一个元素来自输入的另外一个序列。结果输出到指定容器
void test()
{
	{
		vector<int> vec(6);

		std::fill(vec.begin(), vec.end(), 2);
		print_all(vec.begin(), vec.end());

		//将从第二个元素开始的3个元素修改为5
		std::fill_n(vec.begin() + 1, 3, 5);
		print_all(vec.begin(), vec.end());
	}
	{
		vector<int> vec(6);

		std::generate(vec.begin(), vec.end(), []{ return rand() % 10; });
		print_all(vec.begin(), vec.end());

		//将前三个元素修改为1 2 3
		std::generate_n(vec.begin(), 3, []{static int i = 1; return i++; });
		print_all(vec.begin(), vec.end());
	}
	{
		vector<int> vec = { 1, 2, 3, 4, 5 };
		std::transform(vec.begin(), vec.end(), vec.begin(), [](int x){return x*x; });
		print_all(vec.begin(), vec.end());

		vec = { 1, 2, 3, 4, 5 };
		vector<int> vec2 = { 2, 3, 4, 5, 6, 9 };
		//将vec2中的元素逐次对应相加到vec中
		std::transform(vec.begin(), vec.end(), vec2.begin(), vec.begin(), [](int x, int y){ return x + y; });
		print_all(vec.begin(), vec.end());
	}
	{

	}
}

//        删除和替换算法 15个
//copy    : 将一个范围中的元素拷贝到新的位置处 
//copy_backward : 将一个范围中的元素按逆序拷贝到新的位置处, 即：反向复制,从最后的元素开始复制，直到首元素复制出来。
//                复制操作是从last-1开始，直到first结束.返回一个迭代器，指出已被复制元素区间的起始位置
//copy_if :	将一个范围中满足给定条件的元素拷贝到新的位置处
//copy_n  : 拷贝 n 个元素到新的位置处
void test_copy()
{
	{   //copy copy_backward copy_if copy_n
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		vector<int> v2;
		v2.resize(v1.size());

		std::copy(v1.begin(), v1.end(), v2.begin());
		print_all(v2.begin(), v2.end());

		v2.resize(v1.size() * 2);
		std::copy(v1.begin(), v1.end(), v2.begin() + 2);
		std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));  std::cout << "\n";

		std::copy(v1.begin() + 1, v1.end(), v1.begin()); //将元素依次向左覆盖原元素
		print_all(v1.begin(), v1.end());  // 2 3 4 5 6 6

		vector<int> v3(v1.size());
		auto it = std::copy_if(v1.begin(), v1.end(), v3.begin(), [](int e){ return e % 2 == 0; }); //只拷贝偶数
		print_all(v3.begin(), it); // 2 4 6 6

		v3.clear();
		std::copy_n(v1.begin() + 1, 3, std::back_inserter(v3));
		print_all(v3.begin(), v3.end());
	}
	{
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		auto iter = std::copy_backward(v1.begin(), v1.begin() + 2, v1.end()); //从后向前复制，复制到从结尾开始的后两个元素
		print_all(v1.begin(), v1.end()); // 1 2 3 4 1 2
		cout << "copy elems : ";	print_all(iter, v1.end());
	}
	std::cout << "======================\n";
}

//swap: 交换元素
//iter_swap: 通过迭代器进行元素的交换
//swap_ranges: 区间元素交换
void test_swap()
{
	{
		vector<int> v1 = { 1, 2, 3, 4 };
		vector<int> v2 = { 5, 6, 7, 8, 9 };

		std::swap(v1, v2);
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		v2.swap(v1);
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		vector<int>().swap(v2);  //释放了v2的内存占用
		print_all(v2.begin(), v2.end());
	}
	{
		vector<int> v1 = { 1, 2, 3, 4, 5 };
		std::swap(v1[0], v1[1]);
		std::iter_swap(&v1[3], &v1[4]);
		print_all(v1.begin(), v1.end());
	}
	{
		vector<int> v1 = { 1, 2, 3, 4 };
		vector<int> v2 = { 5, 6, 7, 8, 9 };
		std::swap_ranges(v1.begin() + 1, v1.end(), v2.begin()); //将v1从第二个元素后的所有依次与v2从开始元素进行交换
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());
	}
	std::cout << "======================\n";
}

//replace: 将指定元素值替换为新值
//replace_if: 如果满足谓词条件则替换
//replace_copy: 将区间1的元素拷贝到区间2，但是替换某元素值为新值，其他不变
//replace_copy_if: 将区间1的元素拷贝到区间2，但是替换满足谓词条件的某元素值为新值，其他不变
void test_replace()
{
	{	//replace
		vector<int> v1 = { 3, 2, 3, 3, 4, 5, 3 };
		std::replace(v1.begin() + 1, v1.end(), 3, 9); ///将v1从第二个元素后的所有值为3的元素替换为9
		print_all(v1.begin(), v1.end());
	}
	{	//replace_if
		vector<int> v1 = { 1, 2, 3, 3, 4, 5, 3 };
		std::replace_if(v1.begin() + 1, v1.end(), [](int e){ return e >= 3; }, 9); //将所有大于等于3的元素替换为9
		print_all(v1.begin(), v1.end());
	}
	{	//replace_copy
		const vector<int> v1 = { 1, 2, 3, 3, 4, 5, 3 };
		vector<int> v2(v1.size());
		std::replace_copy(v1.begin(), v1.end(), v2.begin(), 3, 8); //将v1中所有元素复制到v2中，但是等于3的元素直接替换为8，不改变v1
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());
	}
	{	//replace_copy_if
		vector<int> v1 = { 1, 2, 3, 3, 4, 5, 3 };
		vector<int> v2(v1.size());
		std::replace_copy_if(v1.begin(), v1.end(), v2.begin(), [](int e){ return e >= 3; }, 8); //将v1中所有元素复制到v2中，如果有值满足谓词条件则替换为8，不改变v1
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		std::replace_copy_if(v1.begin(), v1.end(), v1.begin(), [](int e){ return e >= 3; }, 8); //原地置换
		print_all(v1.begin(), v1.end());
	}
	std::cout << "======================\n";
}

//remove: 将一个范围中值等价于给定值的元素删除.不会真正删除容器中的元素(只是后移)。
//        返回一个新的end()，即为原来的区间移除指定值并且元素前移后的末尾的下一个位置。但是原来容器的end()并不会改变。
//remove_if: 从序列中删除满足谓词条件的元素
//remove_copy : 拷贝一个范围的元素，将其中值等价于给定值的元素删除
//remove_copy_if : 拷贝一个范围的元素，将其中值满足给定条件的元素删除
void test_remove()
{
	{	//remove
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		auto it = std::remove(v1.begin(), v1.end(), 3); //"删除"容器中的所有的3，函数返回新区间最后一个元素的下一个位置  
		print_all(v1.begin(), v1.end());	//1 2 4 4 2 1 2 1 (remove了两个3，所有最后位置的2个元素仍然保持原值)
		print_all(it, v1.end());

		vector<int> v2 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		it = v2.erase(std::remove(v2.begin(), v2.end(), 3), v2.end()); //如果要删除东西的话就在remove的后接上erase
		print_all(v2.begin(), v2.end());	//1 2 4 4 2 1
	}
	{	//remove_if
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		auto it = std::remove_if(v1.begin(), v1.end(), [](int e){ return e > 3; }); //"删除"所有大于3的元素
		print_all(v1.begin(), it); //显示新区间上的元素
		print_all(it, v1.end());   //显示遗留元素
	}
	{	//remove_copy
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		vector<int> v2(v1.size());
		// 将 intList 中除值为34以外的元素，输出到temp1中，不改变 intList。  
		auto it = std::remove_copy(v1.begin(), v1.end(), v2.begin(), 3);
		print_all(v2.begin(), it); //显示新区间上的元素
	}
	{	//remove_copy_if
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		vector<int> v2(v1.size());
		auto it = std::remove_copy_if(v1.begin(), v1.end(), v2.begin(), [](int e){ return e > 3; });
		print_all(v2.begin(), it);
	}
	std::cout << "======================\n";
}

//unique ：从输入序列中"删除"所有相邻的重复元素,不会真正删除容器中的元素(只是后移)。
//unique_copy: 从指定序列中拷贝不重复元素到新序列里，原序列不变
void test_unique()
{
	{	//unique
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 2, 1 };

		std::sort(v1.begin(), v1.end());	//注意：unique只是前后比较相等，因此序列需要排序
		auto it = std::unique(v1.begin(), v1.end());
		print_all(v1.begin(), v1.end());	//整个序列
		print_all(v1.begin(), it);			//新序列区间

		it = std::unique(v1.begin(), v1.end(), [](int e1, int e2){ return e1 == e2; }); //默认即是相等比较
		print_all(v1.begin(), v1.end());	//整个序列
		print_all(v1.begin(), it);			//新序列区间
	}
	{	//unique_copy
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1, 0 };
		vector<int> v2(v1.size());
		std::sort(v1.begin(), v1.end());	//注意：unique_copy只是前后比较相等，因此序列需要排序

		auto it = std::unique_copy(v1.begin(), v1.end(), v2.begin());
		print_all(v2.begin(), it); //显示新区间上的元素
	}
	std::cout << "======================\n";
}

//     排序和通用算法 14个
//merge             : 合并两个有序序列，存放到另一个序列。重载版本使用自定义的比较
//inplace_merge     : 合并两个有序序列，结果序列覆盖两端范围。重载版本使用输入的操作进行排序
//nth_element       : 将范围内的序列重新排序，使所有小于第n个元素的元素都出现在它前面，而大于它的都出现在后面
//partial_sort      : 对序列做部分排序，被排序元素个数正好可以被放到范围内
//partial_sort_copy : 与partial_sort类似，不过将经过排序的序列复制到另一个容器
//partition         : 对指定范围内元素重新排序，使用输入的函数，把结果为t r ue的元素放在结果为fal se的元素之前
//stable_partition  : 与partition类似，不过不保证保留容器中的相对顺序
//random_shuffle    : 对指定范围内的元素随机调整次序。重载版本输入一个随机数产生操作
//reverse           : 将指定范围内元素重新反序排序
//reverse_copy      : 与reverse类似，不过将结果写入另一个容器
//rotate            : 将指定范围内元素移到容器末尾，由middle指向的元素成为容器第一个元素
//rotate_copy       : 与rotate类似，不过将结果写入另一个容器
//sort              : 以升序重新排列指定范围内的元素。重载版本使用自定义的比较操作
//stable_sort       : 与sort类似，不过保留相等元素之间的顺序关系(即：稳定排序) 

//! reverse reverse_copy rotate rotate_copy
void test_reverse_rotate()
{
	{	// reverse reverse_copy
		std::cout << "--------------   reverse reverse_copy   --------------\n";
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		vector<int> v2;

		std::reverse(v1.begin(), v1.end());
		print_all(v1.begin(), v1.end());

		std::reverse_copy(v1.begin(), v1.end(), std::back_inserter(v2));
		print_all(v2.begin(), v2.end());
	}
	{	// rotate rotate_copy
		std::cout << "--------------   rotate rotate_copy   --------------\n";
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		vector<int> v2;

		std::rotate(v1.begin(), v1.begin() + 2, v1.end());
		print_all(v1.begin(), v1.end());

		std::rotate_copy(v1.begin(), v1.begin() + 2, v1.end(), std::back_inserter(v2));
		print_all(v2.begin(), v2.end());
	}
	std::cout << "======================\n";
}

//! 算数数值算法 
//accumulate: iterator对标识的序列段元素之和，加到一个由val指定的初始值上。重载版本不再做加法，而是传进来的二元操作符被应用到元素上
//partial_sum: 创建一个新序列，其中每个元素值代表指定范围内该位置前所有元素之和。重载版本使用自定义操作代替加法
//inner_product: 对两个序列做内积(对应元素相乘，再求和)并将内积加到一个输入的初始值上。重载版本使用用户定义的操作
//adjacent_difference: 创建一个新序列，新序列中每个新值代表当前元素与上一个元素的差。重载版本用指定二元操作计算相邻元素的差
void test_numeric_algorithm()
{
	{	// accumulate
		std::cout << "--------------------    accumulate   --------------------\n";
		vector<int> vec = { 1, 2, 3, 4, 5 };
		int total = 0;
		total = std::accumulate(vec.begin(), vec.end(), 0);
		cout << "total = " << total << "\n";

		total = 1;
		total = std::accumulate(vec.begin(), vec.end(), total, [](int x, int total){ return total *= x; });
		cout << "total = " << total << "\n";
	}
	{	// partial_sum
		std::cout << "--------------------    partial_sum   --------------------\n";
		vector<int> vec = { 1, 2, 3, 4, 5 };
		vector<int> vec2(vec.size());
		std::partial_sum(vec.begin(), vec.end(), vec2.begin()); //部分和，vec2[i] = vec[0]+...+vec[i]
		print_all(vec2.begin(), vec2.end());

		std::partial_sum(vec.begin(), vec.end(), vec2.begin(), std::multiplies<int>()); //部分乘
		print_all(vec2.begin(), vec2.end());
	}
	{	// inner_product
		std::cout << "--------------------    inner_product   --------------------\n";
		vector<int> vec1 = { 1, 2, 3, 4 };
		vector<int> vec2 = { 1, 1, 1, 1 };

		int total = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
		cout << "total = " << total << "\n";
		print_all(vec2.begin(), vec2.end());

		total = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0, plus<int>(), minus<int>());
		cout << "total = " << total << "\n";
		print_all(vec2.begin(), vec2.end());
	}
	{	// adjacent_difference
		std::cout << "--------------------    adjacent_difference   --------------------\n";
		vector<int> vec1 = { 1, 2, 3, 4 };
		vector<int> vec2 = { 1, 1, 1, 1 };

		std::adjacent_difference(vec1.begin(), vec1.end(), vec2.begin());
		print_all(vec2.begin(), vec2.end());

		std::adjacent_difference(vec1.begin(), vec1.end(), vec2.begin(), multiplies<int>());
		print_all(vec2.begin(), vec2.end());
	}
}


int main()
{
	std::cout << "===================\n";

	test_copy();
	std::cout << "===================\n";

	//test_numeric_algorithm();
	std::cout << "===================\n";

	//test_heap_algorithm();
	std::cout << "===================\n";

	getchar();
	return 0;
}