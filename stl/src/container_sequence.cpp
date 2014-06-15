#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <forward_list>
#include <algorithm>
#include <numeric>   // for std::accumulate
using namespace std;

template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

void test_array()
{
	std::cout << "--------------   array   --------------\n";
	const int num = 10;
	std::array<int, num> arr;
	arr.fill(0);

	std::generate_n(arr.begin(), 10, []{return rand() % 100; });
	print_all(arr.begin(), arr.end());

	cout << arr.size() << "\t" << arr.max_size() << "\n";
	cout << *(arr.begin()) << " " << arr[1] << " " << arr.at(2) << " " << arr.back() << "\n";

	arr.front() = 1;
	arr.back() = 99;
	print_all(arr.begin(), arr.end());
}

void test_forward_list()
{
	std::cout << "--------------   forward_list   --------------\n";
	std::forward_list<int> flist;

	flist.push_front(4);
	flist.push_front(20);
	flist.emplace_front(9);
	flist.insert_after(++flist.begin(), 20);
	flist.emplace_after(++flist.begin(), 88);

	cout << "flist中的元素: " ;  print_all(flist.begin(), flist.end());

	//size_t size = flist.size(); //error 没有size函数！！！
	//auto it = flist.begin() + 1;  // error

	cout << "flist中的元素: ";  print_all(flist.begin(), flist.end());

	int top = flist.front();
	flist.pop_front();

	flist.sort();	//按从小到大排序
	cout << "flist中的元素: ";  print_all(flist.begin(), flist.end());

	flist.reverse();	//反转
	cout << "flist中的元素: ";  print_all(flist.begin(), flist.end());

	int result = std::accumulate(flist.begin(), flist.end(), 0);  //求和
	cout << "和为：" << result << endl;

	flist.remove(20);
	flist.remove_if([](int e){return e > 50; });
	cout << "flist中的元素: ";  print_all(flist.begin(), flist.end());

	std::forward_list<int>().swap(flist);
	if (flist.empty())
		cout << "now the list is empty\n";
}



int main()
{
	test_array();
	std::cout << "======================\n";

	test_forward_list();
	std::cout << "======================\n";
	getchar();
	return 0;
}